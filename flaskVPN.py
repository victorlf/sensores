from flask import Flask, request, Response
from requests import get, post

app = Flask(__name__)
SITE_NAME = 'http://152.84.251.21/'

@app.route('/', defaults={'path': ''})
@app.route('/<path:path>', methods=['GET','POST'])
def proxy(path):
    global SITE_NAME
    if request.method=='GET':
        return get(f'{SITE_NAME}{path}').content
    elif request.method=='POST':
        resp = post(f'{SITE_NAME}{path}',json=request.get_json())
        excluded_headers = ['content-encoding', 'content-length', 'transfer-encoding', 'connection']
        headers = [(name, value) for (name, value) in resp.raw.headers.items() if name.lower() not in excluded_headers]
        response = Response(resp.content, resp.status_code, headers)
        return response


if __name__ == '__main__':
  app.run(host='0.0.0.0', port=8090)