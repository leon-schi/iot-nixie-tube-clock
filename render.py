with open('time_html_temp.h', 'r') as f:
    template = f.read()

with open('steering.html', 'r') as f:
    html = f.read()
html = html.replace('\n', '\\n')
html = html.replace('"', '\\"')

formatted = template.format(html)
with open('time_html.h', 'w') as f:
    f.write(formatted)