## Scripting Shell 
Select
```
  #!/bin/bash
  PS3='Choose one word: ' 
  select word in "linux" "bash" "scripting" "tutorial" 
  do
    echo "The word you have selected is: $word"
    # Break, otherwise endless loop
    break
  done

  $ ./select.sh
    1) linux
    2) bash
    3) scripting
    4) tutorial
    Choose one word: 2
    The word you have selected is: bash
```


Case
```
  read var;
  case $var in
    1) echo "You selected bash";;
    2) echo "You selected perl";;
    3) echo "You selected phyton";;
    4) echo "You selected c++";;
    5) exit
  esac
```

Arithmetic expressions
```
  formats  $[ expression ]  and $(( expression ))
  
  k=`expr 1900 + 1024`
  k=$(( 5 + 3 ))
  k=$[ 5 + 3 ]
  /!\ : no space around '=', but one space afer [ , (( and +.
```

Expr

    PROC_NR=$(ps -ef|grep java| grep -v grep | grep  "$APPLI_NAME" |wc -l)

Substitution temporaire

    ${var-$sub} : vaut var si var existe, sub sinon
    ${var:-$sub}: vaut var si var est non vide, sub sinon

    
Copy dir to dir

    cd /from/mydir
    tar cf - . | (cd /to/bkp/mydir && tar xfp -)

  
Special chars

    [[]], [] : test. [[]] more flexible than []
    - : current dir. "cd -" 

- http://tldp.org/LDP/abs/html/special-chars.html 

**test** : same as placing the EXPRESSION between [].

    test $a -gt $b && echo "Yes, a>b." || echo "No, a<=b."

	this will return "Yes, a>b." 
	