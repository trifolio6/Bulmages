#######
#Plugins
#######
#README.es
#20080501

Nombre: Enviar documentos por e-mail

Biblioteca: libpluginbf_correo.so

Descripci贸n: <H1><IMG SRC="@CMAKE_INSTALL_PREFIX@/share/bulmages/imagesrc/images/oxygen/actions/mail_send.svg" WIDTH="100"/><BR>Envios por e-mail</H1>
<P>Permite enviar, mediante un bot贸n nuevo en las fichas, los documentos impresos por e-mail directamente. Al pulsar sobre le bot贸n de enviar por e-mail se abre el gestor de correo con un texto y el documento adjunto</P>
<P>El programa utiliza la directiva <B>CONF_EMAIL_CLIENT</B> de los archivos de configuraci贸n. Preste especial atenci胣 al archivo //.bulmages/bulmafact.conf que es el lugar donde se guarda el parametro por defecto.</P>
<P>La primera vez que este plugin es iniciado, arrancar谩 una ventana de di谩logo, que nos permite seleccionar nuestro cliente de correo preferido, si el lugar donde este instalado se encuentra en el PATH de nuestro sistema operativo, tratar谩 de localizar su ruta autom谩ticamente, en caso contrario deberemos presionar el bot贸n "(...)" y seleccionar el programa, una vez seleccionado, pulsar Aceptar.</P>
<P>Una vez instalado el plugin en los presupuestos, pedidos, albaranes, facturas y cobros a clientes aparecer谩 el bot贸n <IMG SRC="@CMAKE_INSTALL_PREFIX@/share/bulmages/imagesrc/images/oxygen/actions/mail_send.svg" WIDTH="32"/> que al ser presionado abrir谩 el cliente de correo configurado y con un email listo para ser enviado y con el documento correspondiente adjunto. La direcci贸n de correo a la que se envia es la que tiene puesta el cliente.</P>
<B>Autor:</B>Daniel Ripoll Osma (info@danielripoll.es)<BR>
<HR>


ParmBD: 

ArchivoSQLpatch: 

ArchivoSQLdeins: 

Dependencias:

Incompatibles:

Categorias: Utilidades genericas;

Orden: 900

Comentarios: Este plugin actualmente es compatible con Thunderbird, Evolution, Kmail y Outlook. (Funciona tanto en Unix como Windows.)
