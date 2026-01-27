*Este proyecto ha sido creado como parte del currículo de 42 por aruiznav*

## DESCRIPCIÓN.
Este proyecto consiste en la instalación y configuración de mi primer servidor. El objetivo es aprender los fundamentos de la administración de sistemas, la gestión de usuarios, la seguridad, la configuración de servicios básicos y la puesta en marcha de un entorno estable sin interfaz gráfica.

En este proyecto se trabaja con particiones cifradas mediante LVM, configuración de SSH, políticas de contraseña, reglas estrictas de sudo, firewall, un hostname específico y un script de monitorización del sistema.

## INSTRUCCIONES
No hay que compilar nada, simplemente encender la máquina virtual. (Hacer previamente o la comprobación del signature o una copia de la maquina virtual para que este no se modifique).

## RECURSOS
- Videos explicativos: He utilizado diferentes videos durante el proceso de realización del proyecto. (Configuración de LVM con cifrado,  SSH y puertos, UFW, políticas de contraseñas...)
- Uso de la IA: El uso de la IA ha sido principalmente como apoyo, útil para comprender conceptos que me resultaron confusos, entender cada paso a la hora de la configuración...

## DESCRIPCIÓN DEL PROYECTO
Elegí Debian como sistema operativo debido a: es más sencillo para principiantes, tiene una instalación más directa, la documentacion oficial y comunitaria es abundante y su sistema de seguridad AppArmor es más fácil que SELinux.

Elegí dos particiones cifradas con LVM para cumplir la norma del proyecto, además esto mejora la seguridad porque los datos quedan protegidos. 

Para la seguridad está AppArmor activo al iniciar, UFW permitiendo solo el puerto 4242, política estrica de contraseñas y SSH configurado sin permitir acceso como root.

En la gestión de usuarios está mi login (*aruiznav*) en los grupos `user42` y `sudo`. 

Los servicios instalados son solo los necesarios: SSH, sudo, UFW, herramientas de monotización y cron para ejecutar el script cada 10 min.

- Debian vs Rocky Linux.
	- Debian. Estable, fácil de usar, mucha documentación, comunidad enorme, menos orientado a grandes empresas.
	- Rocky. Estándar en entornos corporativos, usa SELinux (muy potente), más difícil de configurar, curva de aprendizaje más alta.
- AppArmor vs SELinux.
	- AppArmor. Facil de entender y configurar, usa perfiles por programa.
	- SELinux. Más complejo y estricto, controla todo el sistema con políticas muy detalladas
- UFW vs firewalld.
	- UFW. Muy sencillo, comandos simples, bloquear/permitir puertos es rapidísimo.
	- firewalld. Más complejo, permite zonas y reglas avanzadas, control más específico y dinámico.
- VirtualBox vs UTM.
	- VirtualBox. Muy bueno en la mayoría de PCs, interfaz intuitiva, soporta x86 totalmente.
	- UTM. Pensado especialmente para Apple Silicon, algo más técnico, usa virtualización tipo QEMU.