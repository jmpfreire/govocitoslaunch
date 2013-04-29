/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConfigLauncher.cpp
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

#include "ConfigLauncher.h"

/**
 Constructor, carga el fichero de versiones para conocer la version actual del
 programa, en caso de que no se encuentre el fichero establece la version inicial
 a 2.
 */
ConfigLauncher::ConfigLauncher()
{
	strcpy(pathVersion, "");
	version = 0;
	
	//Creamos el directorio en caso de que no exista
	creaDirectorio(UtilesLauncher::obtenerDireccionConfig());
	creaDirectorio(UtilesLauncher::obtenerDireccionCache());

	//Leemos el fichero de configuracion
	if(!leerFichConfig(UtilesLauncher::direccionConfig("datosVersion1.dat"), *this))
	{
		version = 2;
		strcpy(pathVersion, "http://lia.ei.uvigo.es:8080/dbDetepre/updateGovocitos");
		escribFichConfig(UtilesLauncher::direccionConfig("datosVersion1.dat"), *this);
	}
}

/**
 Destructor.
 */
ConfigLauncher::~ConfigLauncher()
{

}

/**
 Devuelve la version del programa.
 @return int, version del programa.
 */
int ConfigLauncher::getVersion()
{
	return version;
}

/**
 Establece la version nueva del programa.
 @param v, int que contiene el numero de version.
 */
void ConfigLauncher::setVersion(int v)
{
	version = v;
}

/**
 Devuelve el string que contiene el xml con las versiones.
 @return string, path donde se encuentra el xml con las versiones.
 */
string ConfigLauncher::getPathXmlVeriones()
{
	ostringstream flujo;
	
	flujo << pathVersion;
	
	return flujo.str();
}

/**
 Escribe los datos en el fichero de configuracion.
 @param ruta, string con la ruta del fichero de configuraciones.
 @param &data, objeto ConfigLauncher que contiene los datos de configuracion.
 */
void ConfigLauncher::escribFichConfig(string ruta, ConfigLauncher &data)
{
	ofstream fsalida(ruta.c_str(), ios::out | ios::binary);
	
	fsalida.write((char*)&data,sizeof(ConfigLauncher));
	
	fsalida.close();
	
}

/**
 Lee los datos del archivo de configuracion.
 @param ruta, string con la ruta del fichero de configuraciones.
 @param &data, objeto ConfigLauncher que contiene los datos de configuracion.
 @return bool, delvuevel true si existe el fichero y false en caso contrario.
 */
bool ConfigLauncher::leerFichConfig(string ruta, ConfigLauncher &data)
{
	ifstream fentrada(ruta.c_str(), ios::in | ios::binary);

	if (!fentrada)
	{
		return false;
	}
	else
	{
		fentrada.read((char*)&data,sizeof(ConfigLauncher));
		
		fentrada.close();

		return true;
	}
	
}

/**
 Crea un directorio en el caso de que no exista.
 @param path, string con el path del directorio que deseamos crear.
 */
void ConfigLauncher::creaDirectorio(string path)
{	
	if (!Glib::file_test(path, Glib::FILE_TEST_IS_DIR))
	{
		Glib::RefPtr<Gio::File> fich = Gio::File::create_for_path(path) ;
		
		if (Glib::file_test(path, Glib::FILE_TEST_IS_REGULAR))
		{
			if (!fich->remove())
			{
				//cout<<"Error al borrar el fichero"<<endl;
				cout<<"Error while deleting the file"<<endl;
			}
		}
		
		if (!fich->make_directory())
		{
			//cout<<"Error al crear el directorio"<<endl;
			cout<<"Error while creating the folder"<<endl;
		}
	}	
}
