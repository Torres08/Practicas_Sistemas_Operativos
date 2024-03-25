# Modulo I Administracion de Linux

## Sesión 1. Herramientas de administración básicas

#### **1.1: Bash para iniciar el kernel 
Crea un script de bash que automatice todos los pasos vistos en este punto y que guardarás preferiblemente en tu directorio home. Al entrar de nuevo en el sistema sólo tendrás que ejecutar el script para empezar a trabajar en modo root.

nombre: UML_script.sh

Nota: es opcional la copia a tmp -> + eficiencia ya que al apagar se borra dicha copia

```bash
#!/bin/bash

# Opcional: copiar en tmp, para que cuando apagemos la maquina se borre $ cp ruta_del_gz /tmp

cp /home/vboxuser/Documentos/Modulo_I/*.gz /tmp

# ir a tmp y descomprimir con gunzip

cd /tmp

gunzip kernel32-3.0.4.gz Fedora14-x86-root_fs.gz

# Darle permisos de ejecucion

chmod +x kernel32-3.0.4 Fedora14-x86-root_fs

# Ahora ejecutamos

./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
```

Ejecución
```
./UML_script.sh
```

#### **1.2: Valores por omisión para nuevas cuentas**

Visualiza el contenido de los dos archivos anteriores y comprueba cuáles son las opciones por defecto que tendría un usuario que se creara en nuestro sistema. A continuación, crea una cuenta de usuario y visualiza el contenido de los archivos /etc/passwd y /etc/group, y el de directorio /home para comprobar que los nuevos datos se han rellenado conforme a la especificación tomada de /etc/default/useradd y /etc/login.defs.

¿Que hacemos?
1. visualizar /etc/default/useradd, /etc/login.defs, valores por defecto al crear un usuario
2. crea una cuenta: adduser 
- adduser es mejor: es un comando más moderno y mas intuitivo
- nombre voy a escoger: Juan

```bash
cat /etc/default/useradd

	useradd defaults file
	GROUP=100
	HOME=/home
	INACTIVE=-1
	EXPIRE=
	SHELL=/bin/bash
	SKEL=/etc/skel
	CREATE_MAIL_SPOOL=yes

___

cat /etc/login.defs

# *REQUIRED*
#   Directory where mailboxes reside, _or_ name of file, relative to the
#   home directory.  If you _do_ define both, MAIL_DIR takes precedence.
#   QMAIL_DIR is for Qmail
#
#QMAIL_DIR    Maildir
MAIL_DIR    /var/spool/mail
#MAIL_FILE    .mail
# Password aging controls:
#
#    PASS_MAX_DAYS    Maximum number of days a password may be used.
#    PASS_MIN_DAYS    Minimum number of days allowed between password changes.
#    PASS_MIN_LEN    Minimum acceptable password length.
#    PASS_WARN_AGE    Number of days warning given before a password expires.
#
PASS_MAX_DAYS    99999
PASS_MIN_DAYS    0
PASS_MIN_LEN    5
PASS_WARN_AGE    7
#
# Min/max values for automatic uid selection in useradd
#
UID_MIN     500
UID_MAX   60000
#
# Min/max values for automatic gid selection in groupadd
#
GID_MIN     500
GID_MAX   60000
#
# If defined, this command is run when removing a user.
# It should remove any at/cron/print jobs etc. owned by
# the user to be removed (passed as the first argument).
#
#USERDEL_CMD    /usr/sbin/userdel_local
#
# If useradd should create home directories for users by default
# On RH systems, we do. This option is overridden with the -m flag on
# useradd command line.
CREATE_HOME    yes
# The permission mask is initialized to this value. If not specified,
# the permission mask will be initialized to 022.
UMASK       077
# This enables userdel to remove user groups if no members exist.
#
USERGROUPS_ENAB yes
# Use SHA512 to encrypt password.
ENCRYPT_METHOD SHA512
```

hay que tener en cuenta que todos los usuarios se crearan su carpeta en */home*

listar solo nombres
- con cut -d definimos delimitador, que es : -f1 listar f1 y luego la ruta del archivo
```bash
cut -d: -f1 /etc/passwd
```

creo user Juan
```bash
adduser Juan
```

enseñar Juan en /etc/passwd
```bash
cat /etc/passwd | grep Juan
	Juan:x:500:500::/home/Juan:/bin/bash
```

enseñar Juan en /etc/shadow
```shell
cat /etc/shadow | grep Juan
	Juan:!!:19643:0:99999:7:::
```

enseñar Juan en /etc/group
```bash
cat /etc/group | grep Juan
	Juan:x:500:
```

enseñar Juan en /home
```bash 
ls /home | grep Juan
	Juan
```


respondiendo la pregunta,  crea Juan con el UID 500 (es el primero), al igual que con el GID. Por defecto comienza en el 500. Además crea una carpeta en /home 
ya que *CREATE_HOME -> yes*


#### 1.3: Creación de usuarios
1. lee manual para crear cuentas, crea dos o tres cuantas cambiando los valores, usa adduser.

man -> explicar -> hacer -> comprobar
vamos a crear un grupo1 para luego, 
En el man vemos varias flags para personalizar la reacion de user, en este ejemplo vamos a crear el usuario Juan, con un directorio personalizado /home/Pepe_personalizado, con una descripcion "user Pepe" con el flag , tambien se le dara un  UID personalizado

adduser permite las flags de useradd

```
man adduser
addgroup grupo1
addduser
```

creo un usuario Pepe con directorio personalizado, uid: 555 y lo meto en el gruop hermanos
``` bash
adduser --home /home/pepe_personalizado --uid 555 --group Hermanos Pepe
```

creo un usuario Joaquin con directorio personalizado, uid 666, group hermanos, con comentario personalizado , ademas con un expire date definido 2030-12-31
```bash 
adduser --home /home/joaquin_personalizado -c "Comentario personalizado" --uid 666 --group Hermanos --expiredate 2030-12-31 Joaquin
```

vemos en /etc/passwd, /etc/group, /etc/shadow, /home para ver lo que hemos creado

```bash
cat /etc/passwd | grep -E 'Pepe|Joaquin'
	Pepe:x:555:555::/home/pepe_personalizado:/bin/bash
	Joaquin:x:666:666:Comentario personalizado:/home/joaquin_personalizado:/bin/bash
```

```bash
cat /etc/shadow | grep -E 'Pepe|Joaquin'
	Pepe:!!:19643:0:99999:7:::
	Joaquin:!!:19643:0:99999:7::22279:
```

```bash
cat /etc/group | grep -E 'Pepe|Joaquin'
	Hermanos:x:502:Pepe,Joaquin
```

```bash
ls /home
	Juan  joaquin_personalizado  pepe_personalizado
```


2. Elimina alguno de ellos y comprueba que “rastro” ha dejado la cuenta recién eliminada en el sistema.

para borrar 
```bash
man userdel
```

recomendado el uso de deluser, pero en este UML de fedora no tenemos dicho comando.
```bash
userdel pepe
```

el rastro que puede dejar, sin especificar , deja la carpeta de /home por ejemplo, para borrar tmb la carpeta del home hay que especificarle el flag -r
```
ls /home
	Juan  joaquin_personalizado  pepe_personalizado
```


3. Entra (orden su) en el sistema como uno de estos usuarios que has creado y mira qué archivos tiene en su directorio home. La orden sudo permite cambiar el modo de trabajo a modo root específicamente para ejecutar una orden con privilegios de supervisor y tras su ejecución continuar con los privilegios del usuario que abrió la sesión.


```
man su
```

he creado dentro una carpeta documentos para que no este vacia
```
su Joaquin
ls /home/joaquin_personalizado/
	documentos
```

#### **1.4: Archivo /etc/passwd**
Visualiza el archivo /etc/passwd e indica cual es el formato de cada línea de dicho archivo. Para ello también puedes consultar el man o info de Linux. ¿Quién es el propietario de este archivo y cuáles son sus permisos?

``` bash
cat /etc/passwd
```

formato
```
nombre_de_usuario:contraseña:UID:GID:nombre_completo:/ruta/del/directorio_de_inicio:/bin/shell
```

¿Quien es el propietario?
```bash
man ls
```

- `-l` : long list format, asi vemos sus permisos y quien lo posee

formato `ls -l`:
```
permisos del archivo:numero enlaces duros:propietario:grupo propietario :tamaño archivo en bytes:fecha y hora ultima modificacion:nombre archivo
```

```bash
ls -l /etc/passwd 
	-rw-r--r-- 1 root root 997 Oct 14 05:22 /etc/passwd
```

el propietario es root y sus permisos son de lectura y escritura para el propietario por -rw , luego solo de lectura para el grupo root y para otros usuarios

#### 1.5: Archivo /etc/shadow
Visualiza el archivo `/etc/shadow` desde un usuario distinto al root ¿Te da algún problema? ¿Sabes por qué? Intenta averiguarlo.

vamos al user Joaquin
```bash
su Joaquin
cat /etc/shadow
	cat: /etc/shadow: Permission denied
```

vemos que no tenemos permisos ¿por qué?, vamos a listar en formato largo a ver que permisos tenemos sobre dicho archivo

``` bash
ls -l /etc/shadow 
	---------- 1 root root 762 Oct 14 05:22 /etc/shadow
```

¿que significa?
no tiene permisos de lectura, escritura, ejecución a nadie
root tiene privilegios de superusuarios: no se ve limitado

Si los usuarios normales pudieran acceder al archivo `/etc/shadow`, podrían intentar atacar las contraseñas de otros usuarios utilizando técnicas como fuerza bruta o diccionario, sirve para proteger las contraseñas












#### 1.6: Creación de grupos
1. Crea un par de grupos y asignáselos a algunos de los usuarios de tu sistema.

voy a crear dos usuarios basicos, Miguel y Maria, y voy a asignarlos al grupo, que primero voy a crear ,llamado Primos.

```bash 
adduser Miguel && adduser Maria
```

comprobamos que los hemos creado
```bash
cat /etc/passwd | grep -E 'Miguel|Maria'
	Miguel:x:667:667::/home/Miguel:/bin/bash
	Maria:x:668:668::/home/Maria:/bin/bas
```

creamos el grupo primos, vemos que lo hemos creado 

```bash
groupadd Primos
```

```bash 
cat /etc/group | grep "Primos"     
	Primos:x:669:
```


añadimos miguel y maria con gpasswd
```bash 
gpasswd Primos -a Miguel   
	Adding user Miguel to group Primos

gpasswd Primos -a Maria    
	Adding user Maria to group Primos
```

vemos quien esta en el grupo 
```bash
cat /etc/group | grep "Primos"     
	Primos:x:669:Miguel,Maria
```


1. ¿Qué información devuelve la orden id si estás conectado como root?

```bash
id Miguel
	uid=667(Miguel) gid=667(Miguel) groups=667(Miguel),669(Primos)

id Maria
	uid=668(Maria) gid=668(Maria) groups=668(Maria),669(Primos)
```


#### 1.7: Archivo del kernel de Linux
Utilizando la orden (find) que ya conoces para la búsqueda de archivos en el sistema de archivos, anota el nombre absoluto del archivo del kernel de Linux que se ha cargado en el sistema operativo que estás usando en el laboratorio de prácticas para acceso modo root.

1. *¿que archivo queremos buscar?**
- archivo del kernel, aquel que nosotros cargamos
- `./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m`
- es `kernel32-3.0.4`

2. *¿dentro de un user model linux podemos listar dicho archivo?*
UML es un entrono aislado (igual a una VM), y no tiene accesos directo a los archivos del sistema operativo anfitrión, en todo caso lo podemos listar desde el SO anfitrión

dentro de ubuntu
```bash
find / -name "kernel32-3.0.4"
	/tmp/kernel32-3.0.4
```

desde fedora en el UML no encuentra nada ya que esta aislado del kernel, se ejecuta del SO anfitrion "ubuntu".

desde el UML, podemos imprimir información del sistema, específicamente la versión del kernel del SO
```bash
uname -r
	3.0.4
```


muestra los parámetros del kernel que se pasaron durante el inicio del sistema (dentro de fedora)
```bash
cat /proc/cmdline
	ubda=./Fedora14-x86-root_fs mem=1024m root=98:0
```


#### 1.8: Organización del SA
Un programa que se ejecuta en modo root, ¿dónde podría guardar la información temporal de forma que ésta se mantuviese entre arranques del sistema?

se guardan en /var

`/var`: Guarda datos variables, como registros de archivos de registro, correo, bases de datos temporales, y otros datos que pueden persistir entre reinicio del sistema



#### 1.9: Información de los SAs
Los archivos `/etc/fstab` y `/etc/mtab` muestran información sobre los sistemas de archivos que se encuentran montados en el sistema. ¿Cuál es la diferencia entre la información que muestra cada uno de ellos?

1. `etc/fstab` se utiliza para configurar el montaje automático de sistemas de archivos durante el arranque
2. `/etc/mtab` muestra información en tiempo real sobre los sistemas de archivos actualmente montados en el sistema en un momento dado


#### 1.10: Información de los SAs
Edita el archivo `/etc/fstab` del sistema de archivos que estás utilizando en modo root y anota y describe la información que tiene registrada. Si no conoces alguna opción puedes consultar el manual en línea: `man fstab`

``` bash
man fstab
```

para ir a editar solemos usar `nano` o `vi`, en este caso no tenemos vi.
``` bash
nano /etc/fstab

	#
	# /etc/fstab
	#
	
	LABEL=ROOT   /   auto    noatime   1 1
	tmpfs   /dev/shm    tmpfs    defaults    0 0
	tmp   /tmp   tmpfs    rw,mode=1777,fscontext=system_u:object_r:tmp_t:s0    0 0
	devpts   /dev/pts    devpts    gid=5,mode=620    0 0
	sysfs   /sys   sysfs    defaults    0 0
	proc   /proc   proc    defaults    0 0
```

`/etc/fstab` define como se deben montar los SA durante el proceso de arranque del sistema, muestra los SA montados al arranque

formato
```bash
dispositivo de bloque: punto montaje: tipo SA : opciones montaje: dump: pass
```

ejemplo
```bash
/dev/sda1   /mnt/data   ext4   defaults   0   2
```

`/dev/sda1` es el dispositivo de bloque.
`/mnt/data` es el punto de montaje.
`ext4` es el tipo de sistema de archivos, puede tener etiqueta `auto`
`defaults` son las opciones de montaje predeterminadas.
`0` indica que no se realiza copia de seguridad. `dump`
`2` se utiliza para comprobar el sistema de archivos durante el inicio. `pass`

#### 1.11 Archivos de información para los SAs
Compara la información que contienen los cuatro archivos de texto que se han presentado en este apartado `(/etc/fstab, /etc/mtab, /proc/filesystems y /proc/mounts)`. Describe en un párrafo para qué te sirve la información que registra cada archivo


1. `/etc/fstab`
Configura montajes permanentes

3. `/etc/mtab`
Refleja los montaje en tiempo real

5. `/proc/filesystem`
Lista los tipos de sistemas de archivos admitidos

6. `/proc/mounts`
Proporciona información en tiempo real sobre los sistemas de archivos montados







___
## Sesión 2. Herramientas de administración del SA

#### 2.1: Partición de un dispositivo "USB pen drive" o "memory stick"
En esta actividad utilizaremos un dispositivo USB de tipo “pen drive” para establecer particiones. Vamos a crear una tabla de particiones en las que se van a definir dos particiones primarias que se configuraran para albergar dos sistemas de archivos tipo linux, de manera que la primera algergará un SA ext3 y la segunda un ext4. Ambas serán particiones tipo Linux 0x83. El tamaño de las particiones queda a vuestra libre elección pero por lo menos deberían tener
512 MB. Como las particiones que vamos a hacer no van a ser excesivamente grandes vamos a utilizar la herramienta fdisk2. Esta orden se puede manejar básicamente como un programa guiado por menús para la creación y manipulación de la tabla de particiones. Para poder actuar sobre el pen
drive necesitamos saber que existe un archivo especial de dispositivo que actua como interfaz para el dispositivo físico (dispositivo), por ejemplo, /dev/sda3 representa el dispositivo de almacenamiento secundario sobre el que queremos trabajar. La particion es un dispositivo seguido de un número de partición (comenzando por el 1), p.e. /dev/sda2.
A continuación vamos a describir cómo llevaremos a cabo en las aulas el procedimiento para poder realizar la partición de un dispositivo de almacenamiento secundario. Vamos a distinguir
dos procedimientos: partición de un dispositivo simulado mediante un archivo especial de dispositivo y partición de un pen drive

solo nos enfocamos en la parte A ya que es la que preguntan en el examen
###### A) Preparación previa partición de un dispositivo simulado 

vamos a utilizar un dispositivo simulado mediante un archivo`/dev/loop?`

1. Crea los archivos `/dev/loop0` y `/dev/loop1`

`mknod` crea nodos de dispositivo
`b` dispositivo de bloque

```bash
mknod /dev/loop0 b 7 0
mknod /dev/loop1 b 7 1
```

2. Crea un archivo de 20MB y otro de 30 MB en tu SA con las siguientes ordenes:

`dd`  herramienta para copiar y convertir archivos 

estoy creando un archivo `archivo_SA20` en el directorio `/root` y llenarlo con 20 MB de ceros.

```bash
dd if=/dev/zero of=/root/archivo_SA20 bs=2k count=10000
dd if=/dev/zero of=/root/archivo_SA30 bs=3k count=10000
```

`if=/dev/zero` especifica el archivo de entrada el cual dd leera los daros , /dev/zero es un archivo especial que ontiene ceros

`of=/root/archivo_SA20` archivo de salida al que dd escribira los datos, escrive archivo_SA en /root

`bs=2k` tamaño del bloque para leer y escribir datos. Uso bloques de 2KB, dd leera y escribira datos en bloques de 2KB a la vez

`count=10000` indica cuántos vloques de tamaño `bs` se deben copiar. En este caso estoy copiando 10000 bloques de 2KB cada uno, lo que resulta en un archivo de 20 MB (10000 bloques * 2KB/bloque = 20MB)

el otro lo estoy llenando de 30 MB de ceros 


3. Asociamos un archivo de dispositivo loop a cada uno de los archivos que acabas de crear. De esta forma el "disco virtual" que representa el archivo pasará a estar asociado al archivo de dispositivo `/dev/loop0` y `/dev/loop1` 

`losetup` asociar dispositivo de bucle con archivos de imagen de disco
- `/dev/loop0` dispositivo de bucle
- `/root/archivo_SA20` imagen de disco

```bash 
losetup /dev/loop0 /root/archivo_SA20
losetup /dev/loop1 /root/archivo_SA30
```

si hago `mount` a un punto de montaje podre acceder a dicha información
``` bash
mount /dev/loop0 /punto/de/montaje
```

desasociar dispositivo de bucle (recomendado al terminar de usar el dispositivo de bucle)
```bash
losetup -d /dev/loop0
```

4. Comprobamos lo realizado con `fdisk`

```bash
fdisk -l /dev/loop0 /dev/loop1
```

```bash
losetup -a
	/dev/loop0: [6200]:14286 (/root/archivo_SA20)
	/dev/loop1: [6200]:14316 (/root/archivo_SA30)
```

#### 2.2 Creación de SA
El objetivo es simplemente formatear lógicamente las particiones creadas con anterioridad de forma consistente con el tipo de SA que se estableció que iba a ser alojado. En la primera partición crearemos un SA de tipo ext3 y en la segunda un ext4.
La orden que permite establecer un SA de los reconocidos dentro del sistema Linux sobre una partición de disco es mke2fs (consulta el manual en línea para familiarizarte con sus opciones).
El resultado de la ejecución de esta orden es el formateo lógico de la partición escogida utilizando el SA que se ha seleccionado.
Utiliza el manual en línea para conocer cómo ejecutar la orden de creación de SA. mke2fs es la orden genérica para creación de sistemas de archivos.
Como requisito es necesario que establezcas dos etiquetas de volumen para los SAs: LABEL_ext3 para la primera partición y LABEL_ext4 para la segunda. Debería aparecer un listado en pantalla similar al siguiente.

vamos a formatear logicamentes las particiones `/dev/loop0` `/dev/loop1` 
- `/dev/loop0` le asignamos ext3 con el label `LABEL_ext3`
- `/dev/loop1`le asignamos un `ext4 LABEL_ext4`

usamos la función `mke2fs` , da como resultado un formateo lógico de la partición seleccionada

```bash
man mke2fs
```

0. Comprobamos que tenemos las particiones `/dev/loop0` `/dev/loop1`

```bash
losetup -a
```

1. Formatear `/dev/loop0` como `ext3` con etiqueta `LABEL_ext3`:

```bash
mke2fs -t ext3 -L LABEL_ext3 /dev/loop0
```

2. Formatear `/dev/loop1` como `ext4` con etiqueta `LABEL_ext4`:

```bash
mke2fs -t ext4 -L LABEL_ext4 /dev/loop1
```

3. Comprobamos que se ha realizado el formateo lógico

```bash
blkid
	/dev/loop0: LABEL="LABEL_ext3" UUID="1d9122f7-54b1-49b3-a968-dd51f4c75784" SEC_TYPE="ext2" TYPE="ext3"

/dev/loop1: LABEL="LABEL_ext4" UUID="04b10269-1509-4ea9-ba6e-945e09b384d8" TYPE="ext4"
```

```bash
df -T /dev/loop0
df -T /dev/loop1
```

```
tune2fs -l /dev/loop0
tune2fs -l /dev/loop1
```

```
file -s /dev/loop0
file -s /dev/loop1
```
#### 2.3 Personalización de los metadatos del SA
Consultando el manual en línea para la orden tune2fs responde a las siguientes preguntas:
###### (a) ¿Cómo podrías conseguir que en el siguiente arranque del sistema se ejecutara automáticamente e2fsck sin que se haya alcanzado el máximo número de montajes?

`e2fsck` reparar y verificar integridad SA

para programar que se ejecute automaticamente 

```bash
tune2fs -c 1 -i 0 /dev/loop0
```

configuro la particion `/dev/loop0` para que se realice una comporbacion del SA en cada arranque
1. `-c 1` especifico que realice una comporbacion en cada arranque
2. `-i 0` establezco el intervalo en 0 dias

###### (b) ¿Cómo podrías conseguir reservar para uso exclusivo de un usuario username un número de bloques del sistema de archivos?
Queremos asignar un numero especifico de bloques a un usuario en particular 
e2fsck no se utiliza para asignar un número especifico de bloques a un usuario en particular

`tune2fs` es una herramienta que se utiliza para ajustar los parámetros de configuración de sistemas de archvios ext2, ext3, ext4

vamos a reservar un numero especifico de de bloques para un usuario en particular

1. Identificamos el sistema de archivos: en este caso usaremos `/dev/loop0`

```bash
df -T /dev/loop0
	Filesystem Type   1K-blocks  Used Available Use% Mounted on
	LABEL=ROOT auto 1032088 461372 518288  48% /
```

2. reservar bloques con `tune2fs`
la opcion -r permite reserva dbloques para un usuario en especifico. Supongamos que desear reservar 1000 bloques para el usuario "Joaquin" en un sistema de archivos ext4

```bash
sudo tune2fs -r 1000 -L JoaquinReservedBlocks /dev/loop0
	tune2fs 1.41.12 (17-May-2010)
	Setting reserved blocks count to 1000
```

le pongo un label con -L por que no se como reservar bloques exclusivamente para un usuario.

algunos ejemplos del uso de `tune2fs`
https://www.golinuxcloud.com/tune2fs-command-in-linux/


3. verifica la reserva de bloques
Para verificar que se han reservado los bloques correctamente usamos `dumpe2fs`

```bash
tune2fs -l /dev/loop0 | grep "Reserved block count"
	dumpe2fs 1.41.12 (17-May-2010)
	Reserved block count: 1000
```

mostrara la cantidad de bloques reservados en el sistema de archivos



#### 2.4 Montaje de SA

Utiliza el manual en línea para descubrir la forma de montar nuestros SAs de manera que cumplas los siguientes requisitos:
- El SA etiquetado como LABEL_ext3 debe estar montado en el directorio /mnt/SA_ext3 y en modo de solo lectura.
- El SA etiquetado como LABEL_ext4 debe estar montado en el directorio /mnt/LABEL_ext4 y debe tener sincronizadas sus operaciones de E/S de modificación de directorios.

recomendado una etiqueta para montar

1. Comprobamos nuestros dispositivos `/dev/loop0` `dev/loop1`

```bash
losetup -a
	/dev/loop0: [6200]:14286 (/root/archivo_SA20)
	/dev/loop1: [6200]:14316 (/root/archivo_SA30)
```

```bash
file -s /dev/loop0
	/dev/loop0: Linux rev 1.0 ext3 filesystem data
file -s /dev/loop1
	/dev/loop1: Linux rev 1.0 ext4 filesystem data (extents) (huge files)
```


2. montar el SA `/dev/loop0` con label LABEL_ext3 en `/mnt/SA_ext3` en modo solo lectura

creo los puntos de directorios
```
mkdir /mnt/SA_ext3
mkdir /mnt/LABEL_ext4
```


en solo lectura puedes usar la opcion `ro` "read only" o vale con usar el flag `-r`

```
mount -o ro -t ext3 -L LABEL_ext3 /mnt/SA_ext3
	EXT3-fs: barriers not enabled
	kjournald starting.  Commit interval 5 seconds
	EXT3-fs (loop0): mounted filesystem with writeback data mode
```

ahora toca montar el SA etiquetado como LABEL_ext4 con sincronizacion de operaciones de E/S de modificacion de directorios

```bash
mount -o dirsync -L LABEL_ext4 /mnt/LABEL_ext4
	EXT4-fs (loop1): mounted filesystem with ordered data mode. Opts: (null)
```

`-o dirsync` se encarga de sincronización de operaciones de E/S en un SA 

3. Toca comprobar
vemos primero que los mensajes luego de montar indica que se ha realizado correctamente
también podemos hacer un `ls` de los archivos y ver en el mount a ver si se han montado

```bash
mount | grep "/dev/loop0"
	/dev/loop0 on /mnt/SA_ext3 type ext3 (ro)
mount | grep "/dev/loop1"
	/dev/loop1 on /mnt/LABEL_ext4 type ext4 (rw,dirsync)
```


```bash
ls -l /mnt/SA_ext3/
	total 12
	drwx------ 2 root root 12288 Oct 14 12:33 lost+found+

ls -l /mnt/LABEL_ext4
	total 12
	drwx------ 2 root root 12288 Oct 14 12:33 lost+found+
```

comprobamos que es read only en `/mnt/SA_ext3`, dentro de dicho directorio
```bash
touch ejemplo.txt
	touch: cannot touch `ejemplo.txt': Read-only file system
```


#### 2.5 Auto montaje de SA
Escribe las dos líneas necesarias en el archivo /etc/fstab para que se monten automáticamente nuestros dos SA en el arranque del sistema con los mismos requisitos que se han pedido en la Actividad 2.4.

tengo como SA -> `dev/loop0` y `/dev/loop1` y quiero que se arranque automaticamente en el sistema.

quiero -> se arranque automaticamente en el sistema 

en `etc/fstab` agregamos lo siguiente
```bash
LABEL=LABEL_ext3 /mnt/SA_ext3 ext3 ro 0 0
LABEL=LABEL_ext4 /mnt/LABEL_ext4 ext4 rw,dirsync 0 0
```

al agregar estas dos lineas, se especifican las configuraciones de montaje y los puntos de montaje para que el sistema los monte automáticamente durante el proceso de arranque.

#### 2.6 Repositorio de paquetes
Accede a los sitios web especializados que ofrecen software para sistemas operativos Linux y enumera las principales características de cada uno de ellos en base, por ejemplo, a si contiene software abierto y/o propietario, tipos de aplicaciones disponibles, tamaño del sitio en cuanto a la cantidad de software que mantiene, y otras características que considere interesantes.

Algunos ejemplos de web especializados en software para SO linux son:

1. Snapcraft
	- canonical
	- paquetes snap, usado en Ubuntu

2. Flathub
	- paquuetes flatpak
	- fedora

3. KDE Store
	- complemetario del escritorio KDE

4. Gnome Extensions
	- complementario del escritorio GNOME 

5. DebSotre
	- centrados en paquetes .deb
	- devibia






#### 2.7 Trabajo con e gestor de paquetes YUM
Encuentra los archivos de configuración de YUM y explora las distintas órdenes disponibles en YUM ejecutándolas. En concreto, lista todos los paquetes instalados y disponibles, elimina el paquete instalado que te indique el profesor de prácticas, y a continuación vuelve a instalar el mismo paquete haciendo uso de los paquetes que se encuentran disponibles en `/fenix/depar/lsi/so/paquetes`. Para obtener acceso a este directorio del sistema de archivos anfitrión ejecute la siguiente órden de montaje una vez lanzado el sistema operativo User Mode Linux (UML)
```bash
mount none /<directorio-punto-montaje> -t hostfs -o
/fenix/depar/lsi/so/paquetes
```

1. archivos de configuración YUM y distintas ordenes, lista todos los paquetes instalados y disponibles
	archivos de configuración YUM `/etc/yum.conf`
	para explorar la configuración de YUM y las ordenes disponibles
	el paquete a fin de cuentas es un archivo, con yum lo manejamos y listamos con repolist

listar
```bash
yum repolist all
```

buscar
``` bash
yum  serach nombre_paquete
```

instalar
```bash
yum install nombre_paquete
```

borrar
```
yum remove nombre_paquete
```



#### 2.8 Trabajo con e gestor de paquetes RPM
En primer lugar deseamos mostrar cierta metainformación acerca de uno o más paquetes ya instalados. Para ello debes utilizar la orden rpm con las opciones adecuadas. Utiliza el manual en línea si no sabes ya las opciones que debes utilizar.
1. Muestra la información general (nombre, versión, arquitectura, grupo, descripción, etc.) y lista los archivos que contiene un paquete ya instalado haciendo uso de la orden rpm y un único conjunto de opciones.

que paquete instalado tenemos -> vi

busco como se llama el paquete vi
```bash
rpm -qa | grep vi
	+upstart-sysvinit-1.2-2.fc14.i686
	vim-minimal-7.3.056-1.fc14.i686
	sysvinit-tools-2.87-7.dsf.fc14.i686

```
vemos que se llama `	vim-minimal-7.3.056-1.fc14.i686`

listar información general paquete vi
```bash
rpm -qi vim-minimal-7.3.056-1.fc14.i686
	Name    : vim-minimal              Relocations: (not relocatable)
	Version : 7.3.056                       Vendor: Fedora Project
	Release : 1.fc14                    Build Date: Tue Nov 16 12:05:43 2010
	Install Date: Wed Nov 24 15:33:29 2010     Build Host: x86-04.phx2.fedoraproject.org
	Group   : Applications/Editors      Source RPM: vim-7.3.056-1.fc14.src.rpm
	Size    : 723436                       License: Vim
	Signature   : RSA/SHA256, Tue Nov 16 12:31:00 2010, Key ID 421caddb97a1071f
	Packager : Fedora Project
	URL     : http://www.vim.org/
	Summary : A minimal version of the VIM editor
	Description :
	VIM (VIsual editor iMproved) is an updated and improved version of the
	vi editor.  Vi was the first real screen-based editor for UNIX, and is
	still very popular.  VIM improves on vi by adding new features:
	multiple windows, multi-level undo, block highlighting and more. The
	vim-minimal package includes a minimal version of VIM, which is
	installed into /bin/vi for use when only the root partition is
	present. NOTE: The online help is only available when the vim-common
	package is installed.
```

2. Idem que el anterior pero mostrando únicamente los archivos de configuración que contiene el paquete.
listar archivos de configuracion que contiene el paquete, se suele encontrar en directorios como `/etc`
```bash
rpm -qc vim-minimal-7.3.056-1.fc14.i686
	/etc/virc
```

3. Escribe una orden que muestre los paquetes requeridos por un paquete determinado que se encuentre instalado en el sistema. Escriba la orden que devuelva el mismo resultado pero para un paquete no instalado en el sistema.

mostrar pquetes requeridos por un paquete determinado que se encuentra instalado en el sistema
```bash
rpm -qR vim-minimal-7.3.056-1.fc14.i686
	config(vim-minimal) = 2:7.3.056-1.fc14
	libacl.so.1  
	libacl.so.1(ACL_1.0)  
	libc.so.6  
	libc.so.6(GLIBC_2.0)  
	libc.so.6(GLIBC_2.1)  
	libc.so.6(GLIBC_2.11)  
	libc.so.6(GLIBC_2.2)  
	libc.so.6(GLIBC_2.3)  
	libc.so.6(GLIBC_2.3.4)  
	libc.so.6(GLIBC_2.4)  
	libselinux.so.1  
	libtinfo.so.5  
	rpmlib(CompressedFileNames) <= 3.0.4-1
	rpmlib(FileDigests) <= 4.6.0-1
	rpmlib(PayloadFilesHavePrefix) <= 4.0-1
	rpmlib(VersionedDependencies) <= 3.0.3-1
	rtld(GNU_HASH)  
	rpmlib(PayloadIsXz) <= 5.2-1
```

de los paquetes que hemos montado, vamos a ver `nano-2.2.4-1.fc14.i686.rpm`
para un paquete no instalado en el sistema, lo que buscamos es
```bash
rpm --requires -qp nano-2.2.4-1.fc14.i686.rpm
	/bin/sh  
	/bin/sh  
	/sbin/install-info  
	/sbin/install-info  
	config(nano) = 2.2.4-1.fc14
	libc.so.6  
	libc.so.6(GLIBC_2.0)  
	libc.so.6(GLIBC_2.1)  
	libc.so.6(GLIBC_2.11)  
	libc.so.6(GLIBC_2.2)  
	libc.so.6(GLIBC_2.3)  
	libc.so.6(GLIBC_2.3.4)  
	libc.so.6(GLIBC_2.4)  
	libncursesw.so.5  
	libtinfo.so.5  
	rpmlib(CompressedFileNames) <= 3.0.4-1
	rpmlib(FileDigests) <= 4.6.0-1
	rpmlib(PayloadFilesHavePrefix) <= 4.0-1
	rtld(GNU_HASH)  
	rpmlib(PayloadIsXz) <= 5.2-1
```

5. Instala el paquete quota que encontrarás en el directorio de software de la asignatura (directorio que ya has montado en la Actividad 2.7).

Para instala el paquete hacemos uso del flag `-i`
```bash
rpm -i quota-3.17-13.fc14.i686.rpm
error: Failed dependencies:
    libnl.so.1 is needed by quota-1:3.17-13.fc14.i686
    tcp_wrappers is needed by quota-1:3.17-13.fc14.i686
```

faltan dependencias por lo que instalamos
```bash
rpm -i libnl-1.1-12.fc14.i686.rpm tcp_wrappers-7.6-59.fc14.i686.rpm
rpm -i quota-3.17-13.fc14.i686.rpm
```

comprobamos que se ha instalado quota
```bash
rpm -qa | grep quota
	quota-3.17-13.fc14.i686
```

6. Instala y desinstala el paquete sysstat mostrando en pantalla también la máxima información posible acerca del propio proceso de eliminación del paquete.

instalo
```bash
rpm -i sysstat-9.0.6-3.fc13.i686.rpm
	warning: sysstat-9.0.6-3.fc13.i686.rpm: Header V3 RSA/SHA256 Signature, key ID e8e40fde: NOKEY
```

Comprobamos
```bash
rpm -qa | grep sysstat-9.0.6-3.fc13.i686.rpm
	sysstat-9.0.6-3.fc13.i686
```

desisntalar el paquete `systat` y mostrar información detallada
hay que usar el flag `-vv`
```bash
sudo rpm -e -vv sysstat-9.0.6-3.fc13.i686.rpm
```






#### 2.9 Sistema de cuotas para el SA tipo ext3
como establecer sistema de cuotas
objetivo sobre un SA tipo ext3

1. Editar el archivo /etc/fstab y activar el sistema de cuotas de usuario para el SA tipo ext3. Busca cómo se especifica esta opción en el manual en línea. Una ayuda para la búsqueda es que la realices sobre la orden mount y recuerdes que las opciones de montaje vienen especificadas en los apartados: FILESYSTEM INDEPENDENT MOUNT OPTIONS y FILESYSTEM SPECIFIC MOUNT OPTIONS.

https://www.digitalocean.com/community/tutorials/how-to-set-filesystem-quotas-on-ubuntu-20-04

voy a crear como ne el ejercicio 2.1 , 2.2 un SA ext3

tmb le puedes asociar un tamaño, no se si es opcional, por si acaso he hecho uno /dev/loop3 que le asocio un tamaño de 20MB y /dev/loop4 al que no, habria que usar el /dev/loop1 en todo caso (es el mismo /dev/loop3)

crearán un dispositivo de bucle, lo asociarán con un archivo de datos, formatearán ese dispositivo como ext3 y finalmente verificarán el tipo de sistema de archivos en el dispositivo de bucle.
```bash
mknod /dev/loop3 b 7 3
dd if=/dev/zero of=/root/archivo_SA20 bs=2k count=10000 #si no lo tengo lo creo
losetup /dev/loop3 /root/archivo_SA20
mke2fs -t ext3 -L LABEL_ext3 /dev/loop0 # formateo logico
file -s /dev/loop3
```

lo creamos en una carpeta previamente creada
```bash
mount /dev/loop0 /mnt/SA_ext3
```

o lo ponemos directamente en /etc/fstab
```bash
/dev/loop3  /mnt/SA_ext3  ext3  defaults  0  0
```

```bash
mount -a
```

```bash
mount | grep "/dev/loop0"
```

`/etc/fstab` archivo especificar y montar SA 

para activar el sistema de cuotas
1. abre el archivo `/etc/fstab`
2. encuentra la line que corresponnda al SA ext3 /dev/loop3
```bash
/dev/loop3  /mnt/SA_ext3  ext3  defaults,usrquota  0  0
```

- `defaults,usrquota`: `defaults` son las opciones de montaje por defecto, y `usrquota` es la opción que habilita las cuotas de usuario.

2. Montar de nuevo el SA en el espacio de nombres para que se active la opción previamente establecida. Usa la siguiente orden:

```bash 
sudo mount -o remount /mnt/SA_ext3
```

```bash
mount | gep "/dev/loop3"
	/dev/loop3 on /mnt/SA_ext3 type ext3 (rw,usrquota)
```


3. Crear el archivo que permite llevar el control de cuotas de usuario para el SA. El nombre de este archivo es aquota.user. Para ello utiliza la siguiente orden:

```bash
sudo quotacheck -nm /directorio_punto_de_montaje
```
`-n` indica que solo debe verificar la existencia del archivo `aquota.user` y crearlo si no existe.
`-m` se utiliza para verificar y crear archivos de cuotas de usuario (en este caso, `aquota.user`) en el sistema de archivos especificado.

4. Activa el sistema de control de cuotas de usuario
```bash
quotaon -a
```


5. edita la cuota para cada usuario del sistema mediante la siguente orden 
```bash
edquota username
```
Puedes establecer valores para el número máximo de inodos y bloques que el usuario puede utilizar. Sigue las instrucciones del editor y guarda los cambios.

verificar 
```bash 
sudo repquota -a
```

6. Para finalizar estableceremos el periodo de gracia para el límite soft
```bash
edquota -t
```





#### 2.10 Establecer límites sobre recursos de un SA
Establece los límites de bloques e i-nodos para un par de usuarios del sistema UML sobre el que trabajas en el laboratorio

```bash
edquota usuario1
```

```bash
edquota usuario2
```

verificar cuotas

```bash
edquota -a
```
### Sesión 3. Monitorización del sistema


___

### Sesión 4. Automatización de tareas


## Sesión 3. Monitorización del sistema
#### 3.1: Consulta de estadísticas del sistema
Responde a las siguientes cuestiones y especifica, para cada una, la opción que has utilizado (para ello utiliza man y consulta las opciones de las órdenes anteriormente vistas:

1. ¿Cuánto tiempo lleva en marcha el sistema?
```bash
uptime
	18:32:07 up 15 min, 3 users, load average: 0.20, 0.26, 0.16
```
podemos ver que el sistema ha estado encendido 15 min


2. ¿Cuántos usuarios hay trabajando?

`uptime` también dice que hay 3 user activos

1. ¿Cuál es la carga media del sistema en los últimos 15 minutos?
La carga media del sistema en los últimos 15 minutos es la siguiente: 0.20 (para el último minuto), 0.26 (para los últimos 5 minutos) y 0.16 (para los últimos 15 minutos). Estos valores representan la carga promedio del sistema y pueden variar dependiendo de la actividad actual.

#### 3.2 Prioridad de procesos
1. Crea un script o guión shell que realice un ciclo de un número variable de iteraciones en el que se hagan dos cosas: una operación aritmética y el incremento de una variable. Cuando terminen las iteraciones escribirá en pantalla un mensaje indicando el valor actual de la variable. Este guión debe tener un argumento que es el número de iteraciones que va a realizar. Por ejemplo, si el script se llama prueba_procesos, ejecutaríamos:

prueba_procesos.sh
```bash
#!/bin/bash

# se ha de pasar un argumento
if [ $# -ne 1 ]; then
    echo "Uso: $0 <numero_de_iteraciones>"
    exit 1
fi

# numero de iteraciones del primer argumento
num_iteraciones=$1

# inicializo variable
variable=0
variable_operacion=0

# ciclo para realizar operacion y el incremento
for (( i=0; i< num_iteraciones; i++)); do
    # operacion aritmetica, sumo +1
    variable_operacion=$((variable_operacion + 2))
    #iteracion
    variable=$((variable + 1))
done
echo "Num iteraciones = $num_iteraciones"
echo "El valor de la variable es $variable"
```

```bash
chmod +x prueba_procesos.sh
```

```bash
./pueba_procesos 5
	Num iteracioness = 5
	El valor de la variable es 5
```

2. Ejecuta el guión anterior varias veces en background (segundo plano) y comprueba su prioridad inicial. Cambia la prioridad de dos de ellos, a uno se la aumentas y a otro se la disminuyes, ¿cómo se comporta el sistema para estos procesos?

```bash
./prueba_procesos.sh 1000 & ./prueba_procesos.sh 1000 & ./prueba_procesos.sh 1000 &
```

para verificar la prioridad inicial de estos procesos  `ps -o`
flag `-o` para mostrar el pid, valor prioridad `ni` y el comando ejecutado `cmd`

lo ejecutamos con el comando de arriba tmb
```bash
ps -eo pid,ni,cmd
	...
	1258   0 -bash
	1259   0 -bash
	1260   0 -bash
```

tienen prioridad 0


aumentar la prioridad de un proceso
```bash
renice -n -5 -p 1258 
```

```bash
nice -n -5 ./prueba_proceso.sh 1000
```

para disminuirla le damos un valor positivo, como 5

El comportamiento del sistema dependerá de la carga del sistema. 
- aumentar la prioridad puede hacer que un proceso se ejecute mas rapido,pero puede aumentar la carga, viceversa si se disminuye la prioridad

3. Obtén los tiempos de finalización de cada uno de los guiones del apartado anterior.

ver el tiempo de una ejecucion
```bash
time ./prueba_procesos.sh 10000
	real 0m 0.154s
```

ahora con prioridad cambiada
```bash
time nice -n -5 ./prueba_procesos 1000
	real 0m 0.120s
```

#### 3.3 Jerarquia e informacion de procesos
1. La orden pstree muestra el árbol de procesos que hay en ejecución. Comprueba que la jerarquía mostrada es correcta haciendo uso de la orden ps y de los valores “PID" y “PPID" de cada proceso.
```bash
pstree
	init-+-anacron
	     |-auditd---{auditd}
		 |-crond
		 |-login---bash---pstree
		 |-rsyslogd---2*[{rsyslogd}]
		 |-sendmail
		 `-sshd
```

comprobamos con ps
```bash
ps -ef
```


vemos que el PID y PPID coincide con los procesos listados en pstree y ps -ef

3. Ejecuta la orden ps con la opción -A, ¿qué significa que un proceso tenga un carácter “?” en la columna etiquetada como TTY?

obtener una lista de todos los procesos en ejecucion en el sistema
```bash
ps -A
```

si un proceso tiene un carácter ? en la columna de terminal TTY, significa que el proceso no esta asociado a una terminal especifica 




#### 3.4. Estadísticas de recursos del sistema
Responde a las siguientes cuestiones y especifica, para cada una, la orden que has utilizado:
1. ¿Qué porcentaje de tiempo de CPU se ha usado para atender interrupciones hardware?

para ver el porcentaje de tiempo de la CPU utilizado para atender interrupciones de hardware
	`-P` especifica nucleo que queremos ver
	`ALL` para ver todos los nucles

```bash
mpstat -P ALL
	Linux 3.0.4 (localhost)     10/22/23     _i686_    (1 CPU)
	
	12:12:33 CPU %usr   %nice %sys %iowait %irq   %soft  %steal  %guest %idle
	12:12:33 all 0.00 0.00 0.00 0.02 0.00 0.00 0.00 0.00   99.98
	12:12:33   0 0.00 0.00 0.00 0.02 0.00 0.00 0.00 0.00   99.98
```

`%irq` se corresponde a las interrupciones de hardware

2. ¿Y qué porcentaje en tratar interrupciones software?
`%soft` interrupciones software

3. ¿Cuánto espacio de swap está libre y cuánto ocupado?
Para ver el espacio de swap libre y ocupado en el sistema 
```bash
free -m
	total   used   free shared buffers cached
	Mem:       995     57    938      0      5     34
	-/+ buffers/cache:     17    977
	Swap:        0      0      0
```
- swap libre: 0
- used: 0

#### 3.5. Utilización de las órdenes free y watch
Explora las opciones de las que consta la orden free prestando especial atención a las diferentes unidades de medida según las que puede informar acerca de memoria. Además, compare los resultados con los obtenidos usando la orden watch.

```bash
man free
```

`free` proporciona info sobre la memoria en diferentes unidades de medidas

`-b` en bytes
`-k` kilobytes
`-m` megabytes
`-g` gigabytes

para actualizaciones periódicas de la informaciñón de memoria utilizando`watch` puedes combinar varias

ejecuto free cada dos segundos, 
```bash
watch -n `free -m`
```



#### 3.6 Utilización de vmstat
Intente reproducir el escenario justo descrito anteriormente supervisando la actividad del sistema mediante la ejecución periódica de vmstat tal cual se ha descrito, y proporcione como muestra la salida almacenada en un archivo de texto

Escenario,, ejecutar 20 iteraciones de la orden mostrando la informacion cada 2 segundos

para cumplir el escenario, es decir supervisar la actividad del sistema mediante la ejecucion periodica de vmstat con 20 iteraciones mostrando la info cada 2 segundos y almacenando en un arcjivo de texto

```bash
vmstat 2 20 > vmstat_output.txt
```


#### 3.7. Consulta de metadatos de archivo
Anota al menos dos nombres de archivo de dispositivo de bloques y dos nombres de dispositivo de caracteres de tu sistema UML. Anota los nombres de los archivos ocultos de tu directorio de inicio como usuario root que tienen relación con el intérprete de órdenes que tienes asignado por defecto. Ahora efectúa la misma tarea pero en una consola de terminal del sistema Ubuntu que arrancas inicialmente en el laboratorio de prácticas. ¿Qué diferencias encuentras entre los
nombres de los archivos?

buscar nombres de archivo de dispositivo de vloques y dispositivo de caracter
-> busco en el direcotrio `/dev`

nombre de archivo de dispositivo de bloques
1. `dev/sda`: ejemplo de un dispositivo de bloques, un disco duro, tambien podria ser `/dev/loop0`

busca lineas que comienzan por b
```bash
ls -l /dev | grep ^b
```

Nombres de archivos de dispositivo de caracteres:
1. `/dev/tty0`: Un dispositivo de caracteres que se refiere a la consola virtual número 0.
2. `/dev/zero`: Un dispositivo de caracteres que genera un flujo infinito de ceros.

busca lineas que comienzan por c
```bash
ls -l /dev | grep ^c
```

para ver archivos ocultos relacionados con el intérprete de órdenes (como bash), en tu directorio de inicio, son aquellos que empiezan con un punto
```bash
ls -la
```

1. `.bashrc` Este archivo contiene configuraciones para Bash, el interprete de órdenes por defecto
2. `.bash_profile` archivo conf bash
3. `.bash_history` registra historial de comandos ejecutados en Bash

diferencia entre UML y ubuntu podrian ser varias, como el interprete de ordenes usado o el software instalado, diferencia en los dispositivos de bloques.


#### 3.8. Consulta de metadatos de archivo
Conocemos la sintaxis de la orden para obtener un listado en formato largo (“long listing format”). Manteniendo la opción de listado largo añade las opciones que sean necesarias para obtener un listado largo con las siguientes especificaciones:

1. Que contenga el campo “access time” de los archivos del directorio especificado y que esté ordenado por dicho campo.

enseñar campo access time y ordenado por accestime
`-l` formato largo
`-c` muestra el campo access time (atime) y ordena por atime
```bash
ls -lu
```

3. Que contenga el campo “ctime” de los archivos del directorio especificado y que esté ordenado por dicho campo.

`-c` sort by ctime
```bash
ls -lc
drwxr-xr-x 6 torres torres     4096 Oct 10 16:29 'Calibre Library'
```

la penultima columna pone el ctime, cambia segun si queremos el mtime, ctime o el atime

usa `stat` para verlo mejor
```bash
stat prueba_procesos.sh
```


`mtime` representa el tiempo en el que un archivo fue modificado por ultima vez
`atime` tiempo en que un archivo fue accedido por ultima vez
`ctime` tiempo en que se produjo el último cambio en los atributos del archivo


#### 3.9 Metadatos del sistema de archivos df y du
Resuelve las siguientes cuestiones relacionadas con la consulta de metadatos del sistema de archivos:
1. Comprueba cuántos bloques de datos está usando la partición raíz del sistema UML del laboratorio. Ahora obtén la misma información pero expresada en “human readable format”: Megabytes o Gigabytes. Para ello consulta en detalle el manual en línea.

muestyra el espacio en disco utilizado y disponible en las particiones montadas, para que sea human readable `-h`, directorio raiz es `/`
```bash
df -h /
	Filesystem        Size  Used Avail Use% Mounted on
	LABEL=ROOT       1008M  402M  556M  42% /
```

la particion raiz tiene un tamaño de 1GB, de los cuales 400MB estan siendo utilizados


2. ¿Cuántos inodos se están usando en la partición raíz? ¿Cuántos nuevos archivos se podrían crear en esta partición?

verificar cuantos inodos se estan usando en la particion raíz usamos el flag `-i`
```bash
df -i /
	Filesystem        Inodes   IUsed   IFree IUse% Mounted on
	LABEL=ROOT         65536   14665   50871   23% /
```
total de 65536 inodos de los cuales 14665 estan en uso

¿cuantos nuevos archivos se podrían crear en esta partición?
- en el anterior comando, me indica que tengo 50871 inodos libres, esto significa que puedo crear hasta 50871 nuevos archivos o directorios en la particion raíz antes de agotar los inodos

3. ¿Cuál es el tamaño del directorio /etc? ¿Y el del directorio /var? Compara estos tamaños con los de los directorios /bin, /usr y /lib. Anota brevemente tus conclusiones.

comando `du` permite obtener el tamaño de los directorios , usamos el flag `-s` summarize y `-h` human readable para hacerlo comprensible

tamaño directorio `/etc`
```bash
du -sh /etc
	21M /etc
```
- es pequeño por que es un directorio de configuracion

tamaño directorio `/var`
```bash
du -sh /var
	14M /var
```
- puede ser mas grande, en este caso no, suele contener datos variables, como registro y bases de datos de aplicaciones

tamaño del directorio `/bin`
```bash
du -sh /bin
	5.3M /bin
```
- directorio de binarios del sistema 

tamaño directorio `/usr`
```bash
du -sh /usr
	297M /usr
```
- usuariosn , programas y bibliotecas adicionales

tamaño directorio `/lib`
```bash
du -sh /lib
	24M /lib
```
- bibliotecas compartidas


4. Obtén el número de bloques de tamaño 4 KB que utiliza la rama de la estructura jerárquica de directorios que comienza en el directorio /etc. En otras palabras, los bloques de tamaño 4 KB del subárbol cuya raíz es /etc. ¿Cuál es el tamaño de bloque, por omisión, utilizado en el SA?

vamos a usar `du` con el flag `-s` summarize para obtener el tamaño total del directorio, luego dividirlo por el tamaño del bloque por omision utilizand el SA

```bash
du -s /etc
	21056 /etc
```

la salida en bites , luego calcula el numero de bloques de 4KB dividieno ese tamaño entre 4KB (4096)

$$\frac{21056}{4096} = 5 \text{ bloques}$$ rama /etc usa 5 bloques de 4KB

ahora toca el tamaño de bloque por omision., lo veriamos con tune2fs si estuviese montado como con `/dev/loop0` 
en sistemas de archivos como ext4 , comun en linux seria de 4096B, 4KB, aunque si es ext3 o XFS varia



#### 3.10 Creación de enlaces con la orden ln

Construye los mismos enlaces, duros y simbólicos, que muestra la salida por pantalla anterior. Para ello crea los archivos archivo.txt y target_hardLink2.txt y, utilizando el manual en línea para ln, construye los enlaces softLink, hardLink y hardLink2. Anota las órdenes que has utilizado.
¿Por qué el contador de enlaces del archivo archivo.txt vale 2 si sobre el existen un enlace duro hardLink y un enlace simbólico softLink?

1. Crear el archivo `archivo.txt`, `target_hardlink2.txt`

```bash
echo "Hola mundo" > archivo.txt
echo "Adios mundo" > target_hardLink2.txt
```

2. crear enlaces `softlink` `hardlink` `hardlink2`

- enlace duro llamando hardlink a archivo.txt

```bash
ln archivo.txt hardLink
```

- crea enlace simbolico softlink a archivo.txt

```bash
ln -s archivo.txt softLink
```


- creo un segundo enlace duro hardlink2 a target_hardlink2.txt
```bash
ln target_hardLink2.txt hardLink2
```

comprobamos, no hace falta ver los archivos ocultos
```bash
ls -li
	total 16
	14175 -rw-r--r-- 2 root root 11 Oct 24 04:12 archivo.txt
	14175 -rw-r--r-- 2 root root 11 Oct 24 04:12 hardLink
	14238 -rw-r--r-- 2 root root 12 Oct 24 04:12 hardLink2
	14239 lrwxrwxrwx 1 root root 11 Oct 24 04:32 softLink -> archivo.txt
	14238 -rw-r--r-- 2 root root 12 Oct 24 04:12 target_hardlink2.txt
```


*¿Por qué el contador de enlaces del archivo archivo.txt vale 2 si sobre el existen un enlace duro hardLink y un enlace simbólico softLink?*
	Se debe a que el contador de enlaces (antes del user) se refiere al numero total de enlaces duros a un inodo especifico, en caso de `archivo.txt` como `hardLink` están apuntado al mismo inodo, por tanto el contador de enlaces del inodo de `archivo.txt` es 2  (uno para el archivo original y otro para el enlace duro)
	El enlace simbólico `softLink` no incrementa el contador de enlaces del inodo porque apunta a otro archivo (`archivo.txt`) no al inodo directamente
	Por eso tambien target_hardlink.txt tambien tiene 2 enlaces en el contador a pesar de solo tener 1 enlace duro.

#### Actividad 3.11. Trabajo con enlaces
Proporciona las opciones necesarias de la orden ls para obtener la información de metadatos de los archivos de un directorio concreto en los dos casos siguientes:

1. En el caso de que haya archivos de tipo enlace simbólico, la orden debe mostrar la información del archivo al que enlaza cada enlace simbólico y no la del propio archivo de tipo enlace simbólico.

para mostrar info del archivo al que enlaza cada enlace simbólico y no la del propio enlace simbolico -> `-L` deference

```bash
ls -Ll
	total 20
	-rw-r--r-- 2 root root 11 Oct 24 04:12 archivo.txt
	-rw-r--r-- 2 root root 11 Oct 24 04:12 hardLink
	-rw-r--r-- 2 root root 12 Oct 24 04:12 hardLink2
	-rw-r--r-- 2 root root 11 Oct 24 04:12 softLink
	-rw-r--r-- 2 root root 12 Oct 24 04:12 target_hardlink2.txt
```

archivo.txt y el enlace duro hardlink comparten mismo numero inodos (2), ambos apuntan al mismo archivo real

2. En el caso de enlaces simbólicos debe mostrar la información del enlace en sí, no del archivo al cual enlaza. En el caso de directorios no debe mostrar su contenido sino los metadatos del directorio.

mostrar info del enlace simbólico en sí y no del archivo al que enlaza 
`-d` muestra info del directorio

```bash 
ls -ld /directorio
	drwxr-xr-x 2 usuario grupo 4096 Oct 24 12:34 /directorio
```

2-> numero de enlaces duros al directorio (por defecto tiene al menos dos enlaces duros , uno a si mismo y otro al padre)

muestra info detallada del enlace simbolico en el directorio `/directorio`, no de archivo al que enlaza

#### Actividad 3.12. Creación de archivos especiales
Consulta el manual en línea para la orden mknod y crea un dispositivo de bloques y otro de caracteres. Anota las órdenes que has utilizado y la salida que proporciona un ls -li de los dos archivos de dispositivo recién creados. Puedes utilizar las salidas por pantalla mostradas en esta sección del guión para ver el aspecto que debe presentar la información de un archivo de dispositivo.

buena practica crearlo en `/dev` ya que son dispositivos

crear dispositivo bloque
```bahs
mknod /dev/bloques b 8 100
```

- nombre: bloques
- b: dispositivo de bloques
- 8: major
- 100: minor

crear dispositivo caracteres
```bash
mknod /dev/caracteres c 10 101
```
c: dispositivo de caracteres


comprobamos que los hemos creado

```bash
ls -li bloques caracteres
	14241 brw-r--r-- 1 root root  8, 100 Oct 24 05:02 /dev/bloques
	14248 crw-r--r-- 1 root root 10, 101 Oct 24 05:02 /dev/caracteres
```
b y c al principio determinan que son de bloques o de caracteres
## Sesión 4. Automatización de tareas

#### 4.1 Consulta de información sobre procesos demonios
A partir de la información proporcionada por la orden ps encuentre los datos asociados a los demonios atd8 y crond, en concreto: quién es su padre, qué terminal tienen asociado y cuál es su usuario.

ps -> herramienta para listar procesos del sistema

objetivo -> quiero encontrar información sobre los procesos demonio `atd` y `crond`

```bash
ps
	PID TTY      TIME CMD
	1180 tty0 00:00:00 bash
	1210 tty0 00:00:00 ps
```


luego le metemos una tuberia + grep para identificar solo esos dos procesos demonios `grep -E 'atd8|crond' `

```bash
ps -e -o pid,ppid,tty,cmd,user | grep -E 'atd|crond'
	1167 	1 ?    	crond                   	root
	1274 	1 ?    	atd                     	root

```

`-e` formato largo
`-o` especifico que datos quiero ver: PID, PPID, tty(terminal), cmd (comando), user

crond
	PID: 1167
	PPID: 1 (padre es el proceso raiz (init o systemd))
	terminal: no tiene terminal asociada
	user: root
	comando: crond

atd
	PID: 1274
	PPID: 1 (padre es el proceso raiz (init o systemd))
	terminal: no tiene terminal asociada "?"
	user: root
	comando: ATD








#### 4.2 Ejecución postergada de órdenes con at
Crea un archivo genera-apunte que escriba la lista de hijos del directorio home en un archivo de nombre listahome-`date +%Y-%j-%T-$$`, es decir, la yuxtaposición del literal “listahome” yel año, día dentro del año, la hora actual y pid (consulte la ayuda de date).
Lanza la ejecución del archivo genera-apunte un minuto más tarde de la hora actual.
¿En qué directorio se crea el archivo de salida?

vamos a crear el script `genera_apunte.sh`, escribe la lista de hijos del directorio home en un archivo `listahome date +%Y-%j-%T-$$` 

```bash
#!/bin/bash
output_file="listahome-$(date '+%Y-%j-%T')-$$.txt"
ls /home > "$output_file"
```

creo una variable output_file que contiene el nombre del archivo de salida, generado con la fecha actial y el ID del proceso (pid)
luego listo los archivos en el directorio "/home" y redirige la salida al archivo con el nombre calculado

```bash
chmod +x genera_apunte.sh
./genera_apunte.sh
	genera listahome-2023.297-16:31:42-1322.txt
```

ahora toca programar la ejecución del archivo -> un minuto más tarde de la hora actual

```bash
at -f genera_apunte.sh now + 1 minute
```

#### 4.3 Ejecución postergada de órdenes con at (II)
Lanza varias órdenes at utilizando distintas formas de especificar el tiempo como las siguientes:
(será de utilidad la opción -v):

`-v` shows the time the job will be execute before reading the job

1. a medianoche de hoy
```bash
at midnight
```

1. un minuto después de la medianoche de hoy
```bash
at midnight + 1 minute
at 00:01
```

3. a las 17 horas y 30 minutos de mañana
```bash
at 17:30 tomorrow
```

5. a la misma hora en que estemos ahora pero del día 25 de diciembre del presente año
```bash
at 00:00 122523

at -f genera_apunte.sh $(date --date="now + " +"%H:%M %m%d%Y")
```

1. a las 00:00 del 1 de enero del presente año
```bash
at 00:00 01/01
```

6. a la misma hora  pero dentro de un año y un dia despues
```bash
at -f genera_apunte.sh $(date --date="now + 1 months + 1 day" +"%H:%M %m%d%Y")
```

- dentro del parentesis se ejecutara y el resultado pasara como argumento del at
- date -d "" se encarga de calcular el 

Utiliza las órdenes atq y atrm para familiarizarte con su funcionamiento (consulta la ayuda de estas órdenes)

`atq` muestra la lista de trabajos programados con "at" para el usuario actual. Esto te mostrará los numeros de trabajo y las fechas programadas

`atrm <job_number>` Eliina un trabajo programado especifico por su numero de trabajo, el flag 

```bash
# Ver la lista de trabajos programados
atq

# Eliminar un trabajo específico (reemplaza [job_number] con el número de trabajo que deseas eliminar)
atrm [job_number]
```

#### 4.4 Cuestiones sobre at
El proceso nuevo que se lanza al cumplirse el tiempo que se especificó en la orden at....
1. ¿qué directorio de trabajo tiene inicialmente? ¿hereda el que tenía el proceso que invocó a at o bien es el home, directorio inicial por omisión?

cuando se lanza un proceso con `at` el entorno puede variar segñun la configuracion del sistema 

vamos a conprobar el directorio de trabajo inicial

```bash
echo pwd > directorio.txt | at now
```

```bash
pwd
	/root

cat directorio.txt
	/root
```

orden `at` cambia al directorio de trabajo al directorio actual ($PWD) antes de ejecutar el comando
Si cuando se ejecute la tarea `at` se muestra el directorio actual, esto confirma que el directorio de trabajo inicial es el directorio de inicio por omisión

1. ¿qué máscara de creación de archivos umask tiene? ¿es la heredada del padre o la que se usa por omisión?
El valor de la máscara de creacio de archivos (umask) para el proceso lanzado por `at` suele heredar el valor de `umask` del usuario que crea la tarea at

damos un umask de ejemplo y loego lo comporbamos con at
```bash
umask 0022
umask > umask.txt | at now 

cat umask
	0022
```

3. ¿hereda las variables locales del proceso padre? 
las variable locales del proceso padre generalmente no se heredan automáticamente cuando se heredan de `at`

vamos a verlo

este caso no se hereda del proceso padre
terminal
```bash
VARIABLE = "adios mundo"
```

```bash
VARIABLE = "adios mundo"
echo $VARIABLE
	adios mundo

echo $VARIABLE > variable.txt | at now
cat variable.txt
	adios mundo

```

dame un ejemplo donde at intente heredar variable del proceso padre
en este caso no hereda

Experimenta con la orden at lanzando las órdenes adecuadas para encontrar las respuestas. (Puede encontrar información en la ayuda de at)


#### 4.5 Relación padre-hijo con órdenes ejecutadas mediante at
El proceso nuevo que se lanza al cumplirse el tiempo que se especificó en la orden at.... ¿de quién es hijo? Investiga lanzando la ejecución retardada de un script que muestre la información completa sobre los procesos existentes y el pid del proceso actual; el script podría contener lo que sigue:

script.sh (no funciona, explicarlo por mi cuenta)
```bash
echo 'date +%Y-%j-%T' > nombrearchivo.txt 
ps -p $$ >> nombrearchivo.txt
echo Mi pid = $$ >> nombrearchivo.txt
```

cuando ejecuto un proceso programado con `at`, este proceso se convierte en un proceso independiente y se ejecuta como un hijo del demonio `atd`

cuando ejecuto script como una tarea con `at`, se creará un nuevo proceso independiente bajo el contro de `atd`. El proceso creado por `at` será un hijo del demonio `atd` y su PID será diferente del PID del proceso que programó la tarea `at`

Demostracion que el proceso creado por `at` es un hijo independiente del demonio `atd` y que su PID es diferente del PID del proceso que programó la tarea `at`


script3.sh
```bash
#!/bin/bash
echo "Script ejecutado por PID $$" > hola.txt
```

```bash
at -f script3.sh now + 1 minute

cat hola.txt
	Script ejecutado por PID 1711
```

```bash
ps -e | grep at
	1266 ? 00:00:00 atd
```



#### 4.6 Actividad 4.6. Script para orden at
Construye un script que utilice la orden find para generar en la salida estándar los archivos modificados en las últimas 24 horas (partiendo del directorio home y recorriéndolo en profundidad), la salida deberá escribirse el archivo de nombre
“modificados_<año><día>< hora>” (dentro del directorio home). 
Con la orden at provoque que se ejecute dentro de un día a partir de este momento.


en vez de directorio home nos dirigimos al directorio actual por que no tengo directorio home en el UML

objetivo: buscar archivos modificados ultimas 24 horas a partir del directorio actual y los escribira en un archivo con el nombre en formato referencia al dia. luego con at que se ejecute dentro de un dia, no dice expresamente que este dentro del at

script.sh (funciona)
```bash
#!/bin/bash

#directorio actual
current_dir="$(pwd)"

#obten fechas actual formato año dia hora
currrent_date=$(date "+%Y%d%H")

#nombre archivo de salida
output_file="modificados_$current_date"

# Utiliza find para buscar archivos modificados en las ultimas 24h
find $current_dir -type f -mtime -1 > salida.txt

```

at lo configuro fuera
```bash
at -f script.sh now + 1 day
```



#### 4.6 Trabajo con la orden batch
Lanza los procesos que sean necesarios para conseguir que exista una gran carga de trabajo para el sistema de modo que los trabajos lanzados con la orden batch no se estén ejecutando (puede simplemente construir un script que esté en un ciclo infinito y lanzarla varias veces en segundo plano). Utiliza las órdenes oportunas para manejar este conjunto de procesos (la orden
jobs para ver los trabajos lanzados, kill para finalizar un trabajo, …y tal vez también las órdenes fg, bg para pasar de segundo a primer plano y viceversa, < Ctrl-Z> para suspender el proceso en primer plano actual, etc). Experimenta para comprobar cómo al ir disminuyendo la carga de trabajos habrá un momento en que se ejecuten los trabajos lanzados a la cola batch.

script puede ser peligroso por que aumenta la carga de trabajo 

carga_trabajo.sh
```bash
#!/bin/bash
while true; do
        echo "Generating load..."
        for i in {1..1000}; do
            echo "Load: $i"
        done
        sleep 1
    done

```

lanzo procesos que generen carga de trabajo en segundo plano lanzo 3 por ejemplo
```bash
./generate_load > /dev/null & & ./generate_load > /dev/null && ./generate_load > /dev/null & &
```

mostrar los trabajos lanzados
```bash
jobs
	[1]+  Running             ./scriptcarga.sh > /dev/null &
```

matar los procesos que generan carga
```bash
kill %1 %2 %3
```

```bash
jobs
	[1]+  Terminated          ./scriptcarga.sh > /dev/null
```

#### Actividad 4.8. Utilización de las colas de trabajos de
Construye tres script que deberás lanzar a las colas c, d y e especificando una hora concreta que esté unos pocos minutos más adelante (no muchos para ser operativos). Idea qué actuación deben tener dichos script de forma que se ponga de manifiesto que de esas colas la más prioritaria es la c y la menos es la e. Visualiza en algún momento los trabajos asignados a las distintas colas.

script_1
```bash
#!/bin/bash
echo "Script en cola c ejecutado" >> cola_c.log
```

script_2
```bash
#!/bin/bash
echo "Script en cola d ejecutado" >> cola_d.log
```

script_3
```bash
#!/bin/bash
echo "Script en cola e ejecutado" >> cola_e.log
```


toca programar con at y sus colas (tiempo no tiene sentido por que aunque los cambie el orden sigue siendo el del tiempo impuesto, no las colas)
```bash
at -f script_1.sh -q c now + 2 minutes
at -f script_2.sh -q d  now + 3 minutes 
at -f script_3.sh -q e now + 4 minutes 
```

el script de la cola c se programará primero (2 min en el futuro), seguido de la d y la e, 

verificar los trabajos en las colas con `atq`

los he probado y las colas no hacen efecto
```bash
echo '"hola1" > texto7.txt' | at -q f now + 1 minutes
echo '"hola2" > texto8.txt' | at -q c now + 3 minutes
```

segun las colas, c tendria que tener prioridad, pero se sique generando texto 7 antes que el texto 8 a pesar de la prioridad de colas




#### 4.9 Relación padre-hijo con órdenes ejecutadas mediante crontab
https://linuxhandbook.com/crontab/

Al igual que en el apartado anterior sobre quién es el proceso padre del nuestro, lanza el script construido en dicha actividad con una periodicidad de un minuto y analiza los resultados usando crontab.


quiero ejecutar un script cosntruido con una periodicidad de un minuto utilizacon `cron` , primero vot a configurar

abrir archivo crontab en modo edicion
```bash
crontab -e 
```

dentro del archivo de configuracion pongo mi script para que se ejecute cada minuto

```bash
* * * * * /root/script.sh
	se genera el archivo.log del script al minuto
```

otro ejemplo distinto
```bash
0 * * * * echo “Linux is Cool!” >> ~/crontab_log.txt
```

poniendo mintuos a 0 significa que el comando will run every hour, on the hour

script backup
```bash
#! /bin/bash
DATE=$(date +%d-%m-%Y)
# Date in format DAY##-MONTH##-YEAR####
mkdir -p ~/archive/$DATE
# create a folder for today's date in the archive, if archive doesn't exist, make archive 
ls -al ~/Documents > ~/archive/$DATE/contents.txt
# create a text file listing the contents of the documents folder
cd ~/  && tar -cpzf $DATE.docs.backup.gz Documents/*
# change to parent directory to tar /Documents folder
cp ~/$DATE.docs.backup.gz ~/archive/$DATE/documents_archive.gz
# one .gz file is left in the home directory, a clone is sent to our archive under it's date
```


####  4.10 Ejecucion de scripts con crontab (I)
Construye un script que sea lanzado con una periodicidad de un minuto y que borre los nombres de los archivos que cuelguen del directorio /tmp/varios y que comiencen por “core” (cree ese directorio y algunos archivos para poder realizar esta actividad). Utiliza la opción -v de la orden rm para generar como salida una frase de confirmación de los archivos borrados; queremos que el conjunto de estas salidas se añadan al archivo /tmp/listacores.

Prueba la orden crontab -l para ver la lista actual de trabajos (consulte la ayuda para ver las restantes posibilidades de esta orden para gestionar la lista actual de trabajos).


1. creo el directorio `/tmp/varios` y algunoss archiivos para realizar la actividad
```bash
mkdir -p /tmp/varios
touch /tmp/varios/core_file1
touch /tmp/varios/core_file2
```

2. creo el cripts -> borrar los nombres archivos que empiecen por core de `/tmp/varios`

borrar_cores.sh
```bash
#!/bin/bash
find /tmp/varios -name "core*" -type f -exec rm -v {} \ 
```

`-exec rm -v {} \ ` parte de la expresion find que ejecuta el comando rm para eliminar los archivos encontrados
`-v {}` v indica marcador, {} es un marcador , equivale a los nombres de cada arhcivo encontrado
`\ `indica el final de exe

```bash
chmod +x borrar_cores.sh
```

apunta su ruta
```bash
pwd
```

cnfigurar en crontab
```bash
crontab -e
```

```bash
* * * * * rutadelscript/borrar_cores.sh
```


verifico la lista actual de trabajos cprogramados crontab
```bash
corntab -l
```

#### 4.11 Ejecución de scripts con crontab (II)
Para asegurar que el contenido del archivo /tmp/listacores no crezca demasiado, queremos que periódicamente se deje dicho archivo solo con sus 10 primeras líneas (puede ser de utilidad la orden head). Construye un script llamado reducelista (dentro del directorio ~/SO) que realice la función anterior y lance su ejecución con periodicidad de un minuto

si no tienes el directorio `~/SO` crealo
```bash
mkdir -p ~/SO
```

script reducelista.sh
	reducir el contenido de /tmp/listacores a las 10 primeras lineas
```bash
#!/bin/bash
head -n 10 /tmp/listacores > /tmp/listacores_tmp
mv /tmp/listacores_tmp /tmp/listacores
```

das permisos con chmod

ajustamos crontab
```bash
crontab -e
* * * * * ~/SO/reducelista.sh
```

comporbamos 
```bash
crontab -l
```

ahora el script reducelista se encargara de mantener el archivo `/tmp/listacores` limitado a las 10 primeras lineas y se ejecutara periodicamente cada minuto


#### 4.12 Ejecución de scripts con crontab (III)
Construye un sencillo script que escriba en el archivo ~/SO/listabusqueda una nueva línea con la fecha y hora actual y después el valor de la lista de búsqueda, por ejemplo:

*2011-297-12:39:10 - /usr/local/bin:/usr/local/bin:/usr/bin...

Ejecuta este script desde el lenguaje de órdenes y también lánzalo como trabajo crontab y compara los resultados, ¿se tiene en ambos casos la misma lista de búsqueda?

script -> escriba una linea con fecha y hora actual y despues el valor de la lista de busqueda

actualiza_lista.sh (comprobado)
```bash
#!/bin/bash
fecha_actual=$(date "+%Y-%j-%H:%M:%S")
lista_busqueda=$(echo $PATH)
echo "$fecha_actual - $lista_busqueda" >> ~/SO/listabusqueda

```

dale permisos con chmod

configuro en crontab
```bash
* * * * * ~/SO/actualiza_lista.sh
```

la diferencia entre ejecutar el script desde le lenguaje de órdenes y programarlo en crontab es que cuando se ejecuta desde el lenguaje de órdenes, se ejecuta en el constexto actual del usuario y reflejara la lista de búsqueda especifica de ese usuario en ese momento. Cuando se ejecute desde crontab, se ejecuta en su propio contexto y reflejara la lista de búsqueda del enterno de ejecución de crontab

por lo general la lista de busqueda $PATH suele ser la misma, depende de la configuracion del entorno


#### 4.13 Variables de entorno en archivos crontab
Practicamos ahora lo que acabamos de explicar situándonos en lo que hemos realizado en la Actividad 4.11. Construye un script que generará un archivo crontab llamado crontab-reducelista que deberá contener...
	… como primera linea la asignación a la variable PATH de la lista de búsqueda
	actual y además el directorio $HOME/SO
	. después la indicación a cron de la ejecución con periodicidad de 1 minuto del
	script reducelista
Una vez construido crontab-reducelista lánzalo con la orden crontab. Comprueba que con esta nueva lista de búsqueda podremos hacer alusión a reducelista especificando únicamente su nombre independientemente del directorio de trabajo en que nos situemos (no como ocurría en la Actividad 4.11 en que el directorio $HOME/SO no estaba en la lista de búsqueda).


`crontab-reducelista` incluye la asignacion de la variable `PATH` y la programacion de la ejecucion del script `reducelista` con una periodicidad de 1 minuto

```bash
PATH=$PATH:/$HOME/SO
* * * * * $HOME/SO/reducelista
```

hemos configurado la variable path para indicar a /home/so

cargar en crontab (toma el contenido del archivo y lo configura como tarea programada)
```bash
crontab  crontab-reducelista
```

comprobamos
```bash
crontab -l
```


ahora podemos invocar el script reduce lista desde cualquier directorio sin necesidad de especificar la ruta (incluimos $HOME/SO en PATH, resolvemos el porbelam de la 4.11)


#### 4.14 Archivos crontab de diferentes usuarios
Vamos a lanzar un archivo crontab cuyo propietario es otro usuario. Visualiza el contenido del archivo /fenix/depar/lsi/so/ver-entorno y /fenix/depar/lsi/so/crontabver. Comprueba con ls -l que el propietario es el usuario lsi. Sin copiarlos, úsalos para lanzar la ejecución
cada minuto del script /fenix/depar/lsi/so/ver-entorno. Analiza el archivo de salida: ¿de qué línea del archivo /etc/passwd se toman LOGNAME y HOME, de la línea del propietario del archivo crontab o de la línea del usuario que lanza el archivo crontab?


programar tarea de crontab para otro usuario debes ser root
debes usar la cuenta del usuario para la que deseas programar la tarea en crontab

visualizar contenido de los archivos
```bash
cat /fenix/depar/lsi/so/ver-entorno
cat /fenix/depar/lsi/so/crontabver
ls -l /fenix/depar/lsi/so/ver-entorno
ls -l /fenix/depar/lsi/so/crontabver
```

programar la ejeecucion del script /fenix/depar/lsi/so/ver-entorno cada minuto, debes editar el archivo crontab del usuario lsi, de quien es su propietario
```bash
* * * * * /fenix/depar/lsi/so/ver-entorno
```

¿de qué línea del archivo /etc/passwd se toman LOGNAME y HOME, de la línea del propietario del archivo crontab o de la línea del usuario que lanza el archivo crontab?
`e/tc/passwd` se toman las variables `LONGNAME` y `HOME`, estas variables se toman de la línea del usuario que lanza el arhcivo crontab, es decir, del usuario cuya cuenta está siendo utilizada para editar y programar la tarea en crontab

propietario del archivp crontb no tiene relacion directa con estas variables, son especificas del usuario

Si estoy programando tareas como el usuario "lsi" se tomara la línea correspondiente a ese usuario en el archiv `/etc/passwd`
`

#### Actividad 4.15 Ejecucion de scripts con crontab (IV)
El objetivo es ejecutar todos los días a las 0 horas 0 minutos una copia de los archivos que cuelguen de $HOME que se hayan modificado en las últimas 24 horas. Vamos a programar este salvado incremental utilizando la orden find que usábamos en la Actividad 4.6; ahora queremos que se copien los archivos encontrados por find utilizando la orden cpio:

<orden find de la Actividad 4.6> | cpio -pmduv /tmp/salvado$HOME

cpi: puede tomar de la entrada estándar los archivos origen a copiar; con las opciones que se presentan en el ejemplo anterior replica la estructura original manteniendo metadatos de especial interés como usuario propietario y grupo propietario

Una posibilidad interesante es que la copia se haga en un dispositivo que acabamos de montar, y
justo al terminar lo desmontamos; esto aumenta la seguridad de esa copia ante posibles ataques:

```bash
mount /dev/loop0 /directoriosalvados
<orden find> | <orden cpio>
umount /dev/loop0
```

Como última observación, si el dispositivo y punto de montaje usados en esa orden mount noestán en el fstab serán más difíciles de detectar por un intruso que acceda a nuestro sistema.


copia incremental de los archivos modificados en la ultimas 24h desde la carpeta $HOME y copiarlos a un dispositivo montado temporarmente

1. monta el dispositivo destino
```bash
mount /dev/loop0 /destino
```


2. orden find para encontrar los archivos modificados en las ultimas 24 horas
```bash
find $HOME -type f -mtime -1 | cpio -pmduv /destino
```
busco archivos regulares en la carpeta home modificados en las ultimas 24h (-mtime -1) luego utiliza `cpio` oara copiar estos archivos al directorio destino

flags `cpio`
`-p` modo copia
`-m` preserva los metadatos de los archivos
`-d` permite a cpio crear directorio si es necesario
`-u` sobreescribir los archivos existente si encuentra con el mismo nombre
`-v` modo verbose, mostrara mensajes en la salida estandar mientras se realiza la copia para inidcar el progreso y los archivos copiados

3. Desmonta el dispositivo luego de la copia
```bash
umount /dev/loop0
```


copia_incremental.sh
```bash
#!/bin/bash

moutn /dev/loop0 /destino
find $HOME -type f -mtime -1 | cpio -pmduv /destino
umount /dev/loop0

```

permisos al archivo chmod +x

```bash
crontab -e
```

ejecucion diaria a las 0 horas 0 min: midnight
```bash 
0 0 * * * /ruta/al/script/copia_incremental.sh
```

script asume que el dispositivo esta configurado para ser montado

#### Actividad 4.16. Gestión del servicio crond como usuario root
Prueba las siguientes operaciones sobre el demonio crond:
1. Como usuario root, deshabilita/habilita a un determinado usuario para que pueda utilizar el servicio cron; comprueba que efectivamente funciona.
2. Iniciar y terminar el servicio cron. Prueba las siguientes órdenes para iniciar y terminar este servicio:

Iniciar el servicio cron: /sbin/service crond start
Terminar el servicio cron: /sbin/service crond stop


1. deshabilitar/habilitar un usuario para Cron
para deshabilitar a un usuario para el servicio cron edita el archivo `/etc/cron.deny` añadiendo el usuario a prohibir
```bash
echo "usuario" >> /etc/cron.deny
```

para habilitarlo, borralo del archivo

2. Inicia y terminar el Servicio `crond`

inicia
```bash
systemctl start crond
```

detener
``` bash
systemctl stop crond
```

para sistemas que en vez de usar systemctl usan `init.d`
```bash
/sbin/service crond start
```

stop
```bash
/sbin/service crond stop
```

___

#### ACTIVIDAD EXAMEN 1

script prado -> verlo y usarlo, entenderlo

(Ejercicio 4.3)
Programar ejecución script para que se ejecute en momento determinado:
- Comprobar cola at
- Eliminar de la cola

#### ACTIVIDAD EXAMEN 2
Crear archivo cron a partir script 
Especificar tiempo repeticiñn
Habilitar/Deshabilitar servicio