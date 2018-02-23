### Ansible 
-----
Installation
    
    apt install ansible


Edit /etc/ansible/hosts or ~/ansible/hosts: contains hosts to be managed

    [appservers]
    appserver1
    192.168.56.102

Generate ssh public/private key

    ssh-keygen

Copy ssh public key on remote

    ssh-copy-id -i ~/.ssh/id_rsa.pub root@appserver1
    ssh-copy-id -i ~/.ssh/id_rsa.pub asadm@appserver1

Testing

    # ansible all -m ping -u asadm

    192.168.56.101 | SUCCESS => {
    "changed": false, 
    "ping": "pong"
    }
    192.168.56.102 | UNREACHABLE!

### Playbook
----
**Run a playbook**

    root@master-srv:~# ansible-playbook -i hosts playbook.yml


A playbook is composed of tasks in YML file. TASK format:

    - name: task descriptions
      module: option=value

a task call a module. A module has a precise function. Ex: apt, service, command,etc


### Variables
----
Variables Defined in Playbook:

    - hosts: webservers
      vars:
       my_dir: /opt
    - copy: dest={{my_dir}} src=...

### Jinja2
----
Jinja is a template language for Python. It consists of variable replacement and some logics.

    >> from jinja2 import Template
    >> t = Template("Hello {{ name }}!") 
    >> t.render(name="World")
    u'Hello World!'


### Handlers
----
Handlers allow Running Operations On Change. Example. If Apache has just been installed or updated, 
then handle "restart apache"

    tasks:
     - name: install Apache
       apt: name=apache2 update_cache=yes state=latest 
       notify: 
        - restart apache
       
    handlers:
     - name: restart apache
       service: name=apache state=restarted

### Roles
----
Roles use a predefined organization of directories, like maven. According to the role name,
ansible **include** automaticaly **main.yml** files of tasks, handles, vars etc. 

    # mkdir -p roles/apache/{files,templates,tasks,handlers,vars}
    
    # ansible-playbook -i hosts appservers.yml

    appservers.xml
    roles/
     └─ apache
        ├─ handlers
        │  └─ main.yml
        ├─ tasks
        │  └─ main.yml
        └─ vars
           └─ main.yml      

**appservers.xml**

    ---
    - hosts: appservers
     roles:
      - apache

**tasks/main.yml**

    ---
    - name: install Apache
      apt: name=apache2 update_cache=yes state=latest 
      notify: 
       - restart apache

**handlers/main.yml**

    ---
    - name: restart apache
      service: name=apache2 state=restarted

**vars/main.yml**

    ---
    http_port: 8080

**hosts**

    [appservers]
    appserver1
    appserver2

### Template
----
Template copy files to remote machine, after replacing variables.

    - name: server config
      template:
        src: server.xml
        dest: "{{catalina_home}}/conf/"    

*roles/tomcat/templates/server.xml:*
    
    ...
    <Connector port="{{http_port}}" 
    ....
    
Before copying to remote, *http_port* is replaced by its value defined in *roles/tomcat/vars/main.yml:*

    ---
    http_port : 8280


###  Debug
----

    ansible-playbook -vvv ... 

###  YML Syntax
----
- Indentation: 2 spaces
- Dont use TAB, "Syntax Error". Alayws replaces TAB by spaces.(Modify Editor preference, TAB=x spaces)

### References Ansible
----
- Modules: http://docs.ansible.com/ansible/latest/modules_by_category.html
- https://www.grafikart.fr/formations/serveur-linux/ansible


