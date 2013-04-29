## Process this file with automake to produce Makefile.in

## Created by Anjuta

INCLUDES =                                                      \
	-I$(top_srcdir) 				\
	-I$(top_srcdir)/src				\
	-DPIXMAPSDIR=\""$(datadir)"/govocitoslauncher/Iconos/\"       \
	-DDATADIR=\""$(pkgdatadir)"/Glade/\"
	
gladedir = $(datadir)/govocitoslauncher/Glade
glade_DATA = \
	Glade/DialogoActualizacion.glade\
	Glade/DialogoNotasActualiza.glade

pixmaps_dir = $(datadir)/govocitoslauncher/Iconos/
pixmaps__DATA = \
	Iconos/descarga.png\
	Iconos/logoGovocitos.png \
	Iconos/error.png

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(GOVOCITOSLAUNCHER_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = govocitoslauncher

govocitoslauncher_SOURCES = \
	main.cpp           \
	NucleoLauncher.cpp           \
	NucleoLauncher.h           \
	Modulos/DescargaActualizacion.cpp           \
	Modulos/DescargaActualizacion.h           \
	Modulos/ModulosLauncher.cpp           \
	Modulos/ModulosLauncher.h           \
	Interfaz/InterfazLauncher.cpp           \
	Interfaz/InterfazLauncher.h           \
	Modulos/ConfigLauncher.cpp           \
	Modulos/ConfigLauncher.h           \
	UtilesLauncher.cpp           \
	UtilesLauncher.h           \
	Modulos/InstallGovocitos.cpp           \
	Modulos/InstallGovocitos.h           \
	Interfaz/DialogoActulizacion.cpp           \
	Interfaz/DialogoActulizacion.h           \
	Modulos/InstaladorVersion.cpp           \
	Modulos/InstaladorVersion.h           \
	Modulos/XmlInstalador.cpp           \
	Modulos/XmlInstalador.h           \
	Modulos/ConexionBD.cpp           \
	Modulos/ConexionBD.h           \
	Modulos/XmlWebVersion.cpp           \
	Modulos/XmlWebVersion.h           \
	Interfaz/DialogoSeleccionAct.cpp           \
	Interfaz/DialogoSeleccionAct.h

govocitoslauncher_CXXFLAGS = \
	-I/usr/include/mysql  \
	-I/usr/include/mysql++

govocitoslauncher_LDFLAGS = \
	-L/usr/lib           \
	-lmysqlpp            \
	-lmysqlclient

govocitoslauncher_LDADD = $(GOVOCITOSLAUNCHER_LIBS) \
	-lcurl

EXTRA_DIST = $(glade_DATA)

# Remove glade directory on uninstall
uninstall-local:
	-rm -r $(gladedir)
	-rm -r $(datadir)/govocitoslauncher
