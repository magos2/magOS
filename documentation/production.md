## A
Lenteurs + DeadLock Oracle  
Plan d'action

- Rester sur un Noeud Weblogic, pour eliminer la piste du cluster
- Tester
- Activer le debugging JDBC/SQL sur Weblogic  
  Ce profiling permet de verifier l'orgine des lenteurs: code Java ou SQL 
- Generer le rapport AWR
- Etudier les requetes SQL

Une fois les temps de reponses seront ameliores, les DeadLocks en base vont s'estomper. L'inverse est vrai, les mauvais 
temps de reponses augmentent la probabilité des deadlock. 

Pour ne pas fausser le profiling, aucun autre utilisateur ne doit etre  connecte.

A faire:
- Activer les logs GC
- Xms=Xmx=1024Mo

**Solution**  
Suite au profiling Weblogic/SQL, la requête suivante s’est exécuté 500 fois, rien que pour le seul test effectué. L’application passe son temps à exécuter cette requête, 
Ce qui explique la lenteur de la page « gestionPark ». 

Le rapport AWR d’hier sur 1 heure, l’application a passé 1300 seconds, c’est-à-dire 1/3 de son temps, à exécuter cette requête. 
  
La requête « DELETE FROM PARK_TABLE ...»  est lente aussi, 200 seconds par exécution. 

Axes d’amélioration : 
1. Optimiser le temps d’exécution de la première requête, qui est actuellement de 0.54s par exécution. 
2. Revoir le design de l’application, pour réduire le nombre d’appel à cette requête(Pagination,...). 
3. Optimiser le temps d’exécution de la requête « DELETE FROM PARK_TABLE ...» 


## G
D'apres la lecture de la configuration du serveur de recette, il s'en sort:

0. Arborescence
   Repertoire d'installation:
	Utiliser D:\APPLICATION au lieu de D:\Applis
   
   Conf:
	
   Logs:
  
   Pots:

   Java:

 0.1 Context.xml
    Ne pas mettre en dur le chemin dans context.xml, utiliser plutôt un chemin relatif ou une propriété JAVA.  
    
	<Environment name="config/safar" 
				value="D:/Applis/configSafar.properties"
				type="java.lang.String" 
				override="true"/>
	
  Compte admin:
  Un compte "admin" et un role "manager-gui" sont défini. Il faut les supprimer s'il ne sont pas utilisé. 
  En fait la console d'admin n'est pas installé. S'ils sont utilisés, il faudra mettre un password très fort.  
  
  
1. Sizing de la JVM
   La taille minimale(Xms) est à 4000Mo et maximale(Xmx) à 18Go. En environnement de production, il est 
   recommendé d'avoir les deux tailles egales.
   En fait, la JVM va accroitre la HeapMemory(le tas) pendant les premieres heures, ceci impactera les 
   perfomances de l'application pendant cette periode.

   Stack Thread Size: 350Mo, c'est trop grand!. Avec ce paramètre en Production, il y aurait trop de swap. 
   
   A verifier dans l'environnement de production actuelle si l'application a besoin d'autant de Java memory.

2. Garbage Collector(GC)
   Dans l'hypothese de Xmx à 18Go, les pauses GC risquent d'etres longues(dizaines de secondes). 
   Durant ces pauses l'application n'est pas accessible car le GC stop-the-world. il faudrait previligier 
   le "parallel GC"[option -XX:+UseParallelGC], permettant de reduire les temps de pauses.


   Avec le parallelGC la JVM aura plus de fragmentation, il faudrait prevoir des A/R de tomcat plus 
   souvent(Quotidiennement de preference).

3. SSL et Securité
- Utiliser systematiquement le protocol SSL pour communiquer avec des applications tierces. Et ce afin 
  de garantir la confidentialité et l'integrite des donnees.  
  Dans un premier temps il faudrait ouvrir le connector  HTTPS en plus du connector non securisé HTTP. Et demander 
  aux partenir de se conformer à cette exigence de securité. 
- Desactiver les webapp d'administration: manager, manager-gui, et ROOT.


4. Tests de charge 
   A fin de garantir que cette nouvelle version repondra aux exigences de performances, 
   le seul moyen est bien sur des tests de charge.

   SoapUI est un excellent outil pour tester les web services SOAP et REST. De differents de cas de tests 
   permetteront de voir les metriques de l'application sous charge normal, sous forte charge, ou sur une 
   longue durée, etc. Nous pouvons aussi tuner les parametres de la JVM, GC, Pools, etc. 





