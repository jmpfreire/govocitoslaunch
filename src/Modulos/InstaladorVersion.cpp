/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * InstaladorVersion.cpp
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

#include "InstaladorVersion.h"

/**
 Constructor, establece los valores de la version, plataforma, path y descripcion
 de la actualizacion.
 @param ver, int que contiene el numero de version.
 @param plat, string que contiene la plataforma bajo la cual se ejecuta el actualizador.
 @param path, string que contiene el path de descarga del fichero xml.
 @param desc, string que contiene una breve descripcion de la actualizacion actual.
 */
InstaladorVersion::InstaladorVersion(int ver, string plat, string path, string desc)
{
	InstallGovocitos::ultimaVersion = ver;
	InstallGovocitos::plataforma = plat;
	InstallGovocitos::pathXmlListado = path;
	InstallGovocitos::descripcionAct = desc;
}

/**
 Destructor.
 */
InstaladorVersion::~InstaladorVersion()
{

}

/**
 Devuelve el nombre del fichero que se encuentra en la posicion i del vector con
 nombres de los ficheros.
 @param i, int con el indice del vector.
 @return string, nombre del fichero.
 */
string InstaladorVersion::getNombreFichero(int i)
{
	return nombreFichero[i];
}

/**
 Devuelve la ruta del fichero que se encuentra en la posicion i del vector con las
 rutas de los ficheros.
 @parma i, int con el indice del vector.
 @return string, ruta del fichero.
 */
string InstaladorVersion::getRutaFichero(int i)
{
	return rutaFichero[i];
}

/**
 Devuelve el numero de nombres de ficheros almacenados en el vector de nombreFichero.
 @return int, tamaño del vector de nombreFichero.
 */
int InstaladorVersion::getNumFicheros()
{
	return nombreFichero.size();
}

/**
 Añade un nuevo nombre y ruta de fichero a los vectores de nombreFichero y
 rutaFichero.
 @param nombre, string con el nombre del fichero.
 @param ruta, string con la ruta del fichero.
 */
void InstaladorVersion::anadirFichero(string nombre, string ruta)
{
	nombreFichero.push_back(nombre);
	rutaFichero.push_back(ruta);
}