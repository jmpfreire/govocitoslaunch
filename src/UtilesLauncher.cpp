/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * UtilesLauncher.cpp
 * Copyright (C) José Manuel Pintor Freire 2008-2011 <jmpintorfreire@gmail.com>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "UtilesLauncher.h"

/**
 Metodo estatico que Obtiene los datos de los ficheros glade con la informacion de la interfaz y crea
 un puntero a los objetos del sistema.
 @param filename, string con el path del fichero .glade de la interfaz.
 @param *root_node, puntero const char con la etiqueta el objeto de la interfaz.
 @param *widget_name, puntero const char del objeto referente al objeto de la interfaz.
 */
void UtilesLauncher::getWidgetGlade(string filename,const char* root_node,const char *widget_name,...)
{
	Glib::RefPtr<Gnome::Glade::Xml> refXml;
	Gtk::Widget *gui = 0;
	va_list args;
	const char *name;
	
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
		refXml = Gnome::Glade::Xml::create(filename, root_node);
	}
	catch(const Gnome::Glade::XmlError& ex)
	{
		cerr << ex.what() <<endl;
	}
	#else
	auto_ptr<Gnome::Glade::XmlError> error;
	refXml = Gnome::Glade::Xml::create(filename.c_str(), root_node);
	if(error.get())
	{
		cerr << error->what() <<endl;
	}
	#endif
	
	va_start (args, widget_name);
	for (name = widget_name; name; name = va_arg (args, const char *) )
	{
		Gtk::Widget **wid;

		wid = va_arg (args, Gtk::Widget **);
		*wid = refXml->get_widget(name,gui);
	}
	va_end (args);
}

/**
 Metodo estatico que Detecta el sistema operativo en el que nos encontramos y obtiene la direccion por
 defecto de los ficheros de configuracion, cache y glade.
 @return string, ruta completa de los ficheros de configuracion de la aplicacion.
 */
string UtilesLauncher::getDataDir()
{
	string packagedatadir;
	
	#ifdef G_OS_WIN32
	char *win32Dir;
	
	win32Dir = g_win32_get_package_installation_directory_of_module(NULL);
	packagedatadir = Glib::build_filename(win32Dir, "src");
	g_free(win32Dir);
	#else
	packagedatadir = Glib::build_filename(PACKAGE_DATA_DIR, "govocitoslauncher");
	#endif

	return packagedatadir;
}

/**
 Metodo estatico que Devuelve la ruta de los ficheros glade.
 @param file, string con el nombre del fichero.
 @return string, ruta completa del fichero.
 */
string UtilesLauncher::getGladeFile(string file)
{	
	vector<string> datadir;
	
	datadir.push_back(getDataDir());
	datadir.push_back("Glade");
	datadir.push_back(file);
	
	return Glib::build_filename(datadir);
}

/**
 Metodo estatico que Devuelve la ruta de los iconos.
 @param file, string con el nombre del fichero.
 @return string, ruta completa del fichero.
 */
string UtilesLauncher::getIconoFile(string file)
{
	vector<string> pixmapdir;
	
	pixmapdir.push_back(getDataDir());
	pixmapdir.push_back("Iconos");
	pixmapdir.push_back(file);
	
	return Glib::build_filename(pixmapdir);
}

/**
 Metodo estatico que Convierte un double a un string.
 @param valor, double con el numero a convertir.
 @return string, el numero convertido en cadena.
 */
string UtilesLauncher::converString(double valor)
{
	ostringstream flujo;
	
	flujo << valor;
	
	return flujo.str();
}

/**
 Metodo estatico que Convierte un int a un string.
 @param valor, int con el numero a convertir.
 @return string, el numero convertido en cadena.
 */
string UtilesLauncher::converString(int valor)
{
	ostringstream flujo;
	
	flujo << valor;
	
	return flujo.str();
}

/**
 Metodo estatico que Actualiza la vista de la interfaz vaciando todos los eventos pendientes de mostrar.
 */
void UtilesLauncher::actualizarInterfaz()
{
	while(Gtk::Main::events_pending())
	{
		Gtk::Main::iteration();
	}
}

/**
 Metodo estatico que devuelve la localizacion del archivo de configuracion.
 */
string UtilesLauncher::obtenerDireccionConfig()
{
	return Glib::build_filename(Glib::get_user_config_dir(),"govocitoslauncher");
}

/**
 Metodo estatico que Obtiene la direccion del fichero de configuracion.
 @param fichero, string con el nombre del fichero.
 @return string, con el path de la ruta del fichero de configuracion.
 */
string UtilesLauncher::direccionConfig(string fichero)
{
	return Glib::build_filename(obtenerDireccionConfig(), fichero);
}

/**
 Metodo estatico que Obtiene el directorio cache designado por defecto por gtk.
 @return string, direccion del directorio cache.
 */
string UtilesLauncher::obtenerDireccionCache()
{
	#ifdef G_OS_WIN32
	return Glib::build_filename(Glib::get_user_config_dir(),"datosGovocitos");
	#else
	return Glib::build_filename(Glib::get_user_cache_dir(),"govocitoslauncher");
	#endif
}

/**
 Metodo estatico que Devuelve el path completo de la cache de imagenes.
 @param fichero, string, con el nombre con el que se almacena el fichero en la
 cache de imagenes.
 @return string, path completo de almacenamiento.
 */
string UtilesLauncher::direccionCache(string fichero)
{
	return Glib::build_filename(obtenerDireccionCache(), fichero);
}

/**
 Metodo estatico que Borra un fichero del sistema.
 @param ruta, string con el path del fichero a borrar.
 */
bool UtilesLauncher::borraFicheroSistema(string ruta)
{
	if (!Glib::file_test(ruta, Glib::FILE_TEST_IS_DIR))
	{
		Glib::RefPtr<Gio::File> fich = Gio::File::create_for_path(ruta) ;
		
		if (Glib::file_test(ruta, Glib::FILE_TEST_IS_REGULAR))
		{
			if (!fich->remove())
			{
				//cout<<"Error al borrar el fichero"<<endl;
				cout<<"Error while deleting the file"<<endl;
				return false;
			}
		}
	}
	return true;
}

/**
 Metodo estatico que Convierte una cadena a un float.
 @param cadena, string que contiene la cadena a convertir.
 @return int, resultado de la cadena numerica pasada por argumento.
 */
int UtilesLauncher::convertStringToInt(string cadena)
{
	string aux1, aux2;
	size_t found;
	float result, num1, num2;
	int potencia;

	found = cadena.find_last_of(".");

	aux1 = cadena.substr(0, found);
	aux2 = cadena.substr(found + 1);
	potencia = aux2.length();
	
	num1 = atoi(aux1.data());
	num2 = atoi(aux2.data());

	result = (num1 * pow(10.0, potencia)) + num2;

	return result;
}

/**
 Metodo estatico que muestra un Dialogo error.
 @param t, string que contiene el texto del dialogo.
 @param tittle, string que contiene el titulo del dialogo.
 */
void UtilesLauncher::dialogoError(string t, string title)
{
	Gtk::MessageDialog dialogoConf(t, false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, false);
	
	dialogoConf.set_icon_from_file(UtilesLauncher::getIconoFile("error.png"));
	dialogoConf.set_title(title);
	
	dialogoConf.run();
}