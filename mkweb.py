import os
import sys

web_root = '/usr/local/src/webroot'

html = '''
<html>
    <head>
       <title>hello</title>
    </head>
    <body>
       hello world
    </body>
</html>
'''

if len(sys.argv) == 2:
    web_root = sys.argv[1]

if not os.path.exists(web_root):
    os.makedirs(web_root)
    
open(web_root+'/index.html','w').write(html)
