/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * NucleoLauncher.cpp
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

#include "NucleoLauncher.h"

/**
 Constructor, crea los objetos de InterfazLauncher y ModulosLauncher. Ademas establece
 un puntero del controlador a la interfaz.
 */
NucleoLauncher::NucleoLauncher()
: interfazLaunch(new InterfazLauncher()), 
modeloLaunch(new ModulosLauncher())
{
	interfazLaunch->setControlador(*this);

	DialogoSeleccionAct *dialogoSelecN = interfazLaunch->getDialogoSeleccionAct();

	dialogoSelecN->getSkipVersionButton()->signal_clicked().connect(sigc::mem_fun(*this, &NucleoLauncher::skipVersionActual));
	dialogoSelecN->getRemindLaterButton()->signal_clicked().connect(sigc::mem_fun(*this, &NucleoLauncher::remindLaterVersion));
	dialogoSelecN->getUpdateButton()->signal_clicked().connect(sigc::mem_fun(*this, &NucleoLauncher::iniciarActualizacion));
}

/**
 Destructor.
 */
NucleoLauncher::~NucleoLauncher()
{
	delete interfazLaunch;
	delete modeloLaunch;
}

/**
 Devuelve un puntero del objeto de la intefaz.
 @return *InterfazLauncher, puntero del objeto InterfazLauncher.
 */
InterfazLauncher *NucleoLauncher::getInterfazLaunch()
{
	return interfazLaunch;
}

/**
 Comprueba si hay nuevas actualizaciones disponibles.
 @return bool, true si hay nuevas actualizaciones, false en caso contrario.
 */
bool NucleoLauncher::comprobarNuevasActualizaciones()
{
	ConfigLauncher *configuracion;
	InstallGovocitos *instalador;
	ConexionBD conec;
	string plataforma;

	#ifdef G_OS_WIN32
		plataforma = "win32";
	#else
		plataforma = "unix";
	#endif
	
	configuracion = modeloLaunch->getConfigLauncher();
	instalador = modeloLaunch->getInstallGovocitos();

	double version = configuracion->getVersion();

	if(version <= 305062)
	{
		version = 305062;
		configuracion->setVersion(305062);
	}
	
	if(conec.obtenerDatosBD(plataforma ,version, *instalador))
	{
		modeloLaunch->crearInstaladorVersion(instalador->getUltimaVersion(), 
		                                     instalador->getPlataforma(), 
			                                 instalador->getPathXmlListado(),
		                                     instalador->getDescripcionActualizacion());

		//Mostramos la descripcion de la version
		Glib::RefPtr<Gtk::TextBuffer> buf;
		Gtk::TextView *descVer = interfazLaunch->getDialogoSeleccionAct()->getTextViewDescripcion();
		buf = descVer->get_buffer();
		buf->set_text(instalador->getDescripcionActualizacion());
		
		return true;
	}
	
	return false;
}

/**
 Actualiza el sistema govocitos.
 */
void NucleoLauncher::iniciarActualizacion()
{
	DescargaActualizacion *actualizacion;
	ConfigLauncher *configuracion;

	actualizacion = modeloLaunch->getDescargaActualizacion();
	configuracion = modeloLaunch->getConfigLauncher();

		
	//Se encuentra nueva version comenzamos a obtener los ficheros
	interfazLaunch->crearDialogoActuliazcion();

	//Pasamos la interfaz a la descarga
	modeloLaunch->getDescargaActualizacion()->setDialogoProgreso(*interfazLaunch->getDialogoActualizacion());

	//Obtenemos la actualizacion
	if(obtenerDatosDeActualizacion())
	{
		if(descargaDatos())
		{
			DialogoActulizacion *dialogoActualiza;
			InstaladorVersion *installVer;
				
			installVer = modeloLaunch->getInstaladorVersion();
			dialogoActualiza = interfazLaunch->getDialogoActualizacion();

			////Comenzamos la sustitucion de los ficheros descargados
			int numFicheros = installVer->getNumFicheros();

			for(int i = 0; i < numFicheros; i++)
			{
				string path, ruta, nombre;

				nombre = installVer->getNombreFichero(i);
				path = UtilesLauncher::direccionCache(nombre);
				ruta = installVer->getRutaFichero(i) + nombre;

				//Obtenemos la ruta de instalacion
				#ifdef G_OS_WIN32
					char *win32Dir;

					win32Dir = g_win32_get_package_installation_directory_of_module(NULL);		
					ruta = Glib::build_filename(win32Dir, ruta);
				#else
					/*if(nombre == "govocitos")
					{
						ruta = Glib::find_program_in_path("govocitos");
					}
					else
					{
						ruta = Glib::build_filename(PACKAGE_DATA_DIR, ruta);
					}*/
				#endif
				//Sustituimos los ficheros
				Glib::RefPtr<Gio::File> fich = Gio::File::create_for_path(path);
				Glib::RefPtr<Gio::File> fichRemplazo = Gio::File::create_for_path(ruta);
				
				fich->copy(fichRemplazo, Gio::FILE_COPY_OVERWRITE);
			}
			//Borramos los ficheros descargados
			if(!borraCacheDescarga(*installVer, numFicheros))
			{
				//cout<<"Error al borrar los ficheros descargados"<<endl;
				cout<<"Error while deleting the downloaded files"<<endl;
			}
			//Actualizamos el numero de version
			configuracion->setVersion(installVer->getUltimaVersion());
			//Guardamos los datos de la version
			configuracion->escribFichConfig(UtilesLauncher::direccionConfig("datosVersion1.dat"), *configuracion);
			//Habilitamos el boton de cerrar de la aplicacion
			dialogoActualiza->setActiveCerrar();
		}
		else
		{
			//cout<<"Error Fallo en la descarga"<<endl;
			cout<<"Error while downloading"<<endl;

			string titulo = "Update error";
			string texto = "The system can not be update. Try later or contact as support";
			UtilesLauncher::dialogoError(texto, titulo);
			
			//no se encuentra nueva version llamamos a la funcion de salida
			interfazLaunch->cerrarActualizador();
		}
	}
	else
	{
		string titulo = "Update error";
		string texto = "The system can not be update. Try later or contact as support";
		UtilesLauncher::dialogoError(texto, titulo);
		
		//no se encuentra nueva version llamamos a la funcion de salida
		interfazLaunch->cerrarActualizador();
	}
}

/**
 Obtiene los datos de instalacion de la nueva version desponible en el servidor.
 @return bool, true si el fichero xml con los datos de instalacion se obtuvo 
 correctamente y false en caso contrario.
 */
bool NucleoLauncher::obtenerDatosDeActualizacion()
{
	DescargaActualizacion *actualizacion;
	InstaladorVersion *instalador;
	string pathCompleto;

	instalador = modeloLaunch->getInstaladorVersion();
	actualizacion = modeloLaunch->getDescargaActualizacion();

	pathCompleto = instalador->getPathXmlListado() + "/" + instalador->getPlataforma() 
		+ "/" + UtilesLauncher::converString(instalador->getUltimaVersion());
	
	if(actualizacion->descargaFicheroXml(instalador->getPathXmlListado(), "XmlInstalacion.xml"))
	{
		try
		{
			XmlInstalador p(*instalador);
			p.set_substitute_entities(true);
			p.parse_file(UtilesLauncher::direccionConfig("XmlInstalacion.xml"));
		}
		catch(...)
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

/**
 Descarga los ficheros almacenados en el servidor de la nueva actualizacion .
 @return bool, true si la descarga se realizo con exito, false en caso contrario.
 */
bool NucleoLauncher::descargaDatos()
{
	string pathDescarga;
	DescargaActualizacion *actualizacion;
	InstaladorVersion *instalador;
	DialogoActulizacion *dialogoActualiza;

	instalador = modeloLaunch->getInstaladorVersion();
	actualizacion = modeloLaunch->getDescargaActualizacion();
	pathDescarga = instalador->getPathXmlListado();
	dialogoActualiza = interfazLaunch->getDialogoActualizacion();
	
	//Comenzamos la descarga de todos los ficheros
	int numFicheros = instalador->getNumFicheros();

	for(int i = 0; i < numFicheros; i++)
	{
		string path, ruta, nombre;

		nombre = instalador->getNombreFichero(i);

		path = pathDescarga + "/" + nombre;

		//Rellenamos los datos en el dialogo de actualizacion
		dialogoActualiza->actualizaNumFicheros((i + 1), numFicheros);
		dialogoActualiza->actualizaInfoDescarga(0.0, 0.0);
		
		if(!actualizacion->descargaDatos(path, UtilesLauncher::direccionCache(nombre)))
		{
			if(borraCacheDescarga(*instalador, i))
			{
				//cout<<"Error borrando los ficheros descargados"<<endl;
				cout<<"Error while deleting the downloaded files"<<endl;
			}
			
			return false;
		}
	}

	dialogoActualiza->FinalizaDescarga();

	return true;
}

/**
 Borra los ficheros descargados de la nueva actualizacion los cuales se mantenian
 en almacenados en una cache.
 @param &iv, referencia del InstaladorVersion que contiene las rutas y nombres
 de los ficheros descargados.
 @param i, int numero maximo de ficheros a borrar.
 */
bool NucleoLauncher::borraCacheDescarga(InstaladorVersion &iv, int i)
{
	string nombre = "";
	bool toret = true;
	
	for(int j = 0; j < i; j++)
	{
		nombre = iv.getNombreFichero(j);

		if(!UtilesLauncher::borraFicheroSistema(UtilesLauncher::direccionCache(nombre)))
		{
			toret = false;
		}
	}

	return toret;
}

/**
 Se salta la version actual y establece la version para que no se ejecute el 
 actualizador hasta la siguiente version.
 */
void NucleoLauncher::skipVersionActual()
{
	ConfigLauncher *configuracion;
	InstaladorVersion *installVer;
				
	installVer = modeloLaunch->getInstaladorVersion();
	configuracion = modeloLaunch->getConfigLauncher();
	
	//Actualizamos el numero de version
	configuracion->setVersion(installVer->getUltimaVersion());
	//Guardamos los datos de la version
	configuracion->escribFichConfig(UtilesLauncher::direccionConfig("datosVersion1.dat"), *configuracion);

	interfazLaunch->cerrarActualizador();
}

/**
 Cierra el actualizador.
 */
void NucleoLauncher::remindLaterVersion()
{
	interfazLaunch->cerrarActualizador();
}