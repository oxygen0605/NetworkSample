import os
import socket
from mimetypes import guess_type

def index_view(request):
    body = '''
    <html>
    <head>
        <link href="/static/style.css" rel="stylesheet">
    </head>
    <body>
        <h1>Hello World!</h1>
        <img src="/static/image.jpg">
    </body></html>
    '''
    return ('200 OK', [], body)

def file_view(request):
    path = request['PATH_INFO']
    path = path.lstrip('/')  # remove first /
    if not os.path.isfile(path):
        return notfound_view(request)

    ct, _ = guess_type(path)
    if ct is None:
        ct = 'application/octet-stream'
    headers = [
        ('Content-Type', ct),
    ]
    return ('200 OK', headers, open(path, 'rb').read())


def notfound_view(request):
    return ('404 NOT FOUND', [], 'NO PAGE')

patterns = {
    '/static/': file_view,
    '/': index_view,
}

def dispatch(request):
    path_info = request['PATH_INFO']
    for path, view in patterns.items():
        if path_info.startswith(path):
            return view
    return notfound_view

def wsgiapp(environ, start_response):
    request = environ
    view = dispatch(request)
    status, headers, body = view(request)
    if isinstance(body, str):
        body = body.encode('utf-8')
    start_response(status, headers)
    return [body]