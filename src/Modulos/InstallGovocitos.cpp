/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * InstallGovocitos.cpp
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

#include "InstallGovocitos.h"

/**
 Constructor, inicializa todos los atributos a 0 o "".
 */
InstallGovocitos::InstallGovocitos()
{
	ultimaVersion = 0;
	plataforma = "";
	pathXmlListado = "";
	descripcionAct = "";
}

/**
 Destructor.
 */
InstallGovocitos::~InstallGovocitos()
{

}

/**
 Devueve la ultima version de la actualizacion.
 @return int, numero de la version.
 */
int InstallGovocitos::getUltimaVersion()
{
	return ultimaVersion;
}

/**
 Devuelve la plataforma para la cual es la actualizacion.
 @param string, plataforma de la actualizacion.
 */
string InstallGovocitos::getPlataforma()
{
	return plataforma;
}

/**
 Devuelve el path del fichero xml con los datos de instalacion.
 @return string, path del xml con la lista de ficheros a descargar.
 */
string InstallGovocitos::getPathXmlListado()
{
	return pathXmlListado;
}

/**
 Devuelve la descripcion de la actualizacion.
 @return string, descripcion de la actualizacion.
 */
string InstallGovocitos::getDescripcionActualizacion()
{
	return descripcionAct;
}

/**
 Establece la ultima version.
 @param v, int con el numero de version.
 */
void InstallGovocitos::setUltimaVersion(int v)
{
	ultimaVersion = v;
}

/**
 Establece la plataforma de la version.
 @param p, string con la plataforma de la version.
 */
void InstallGovocitos::setPlataforma(string p)
{
	plataforma = p;
}

/**
 Establece el path del xml de instalacion.
 @parma l, string con el path del xml de instalacion.
 */
void InstallGovocitos::setPathXmlListado(string l)
{
	pathXmlListado = l;
}

/**
 Establece la descripcion de la actualizacion.
 @param d, string con la descripcion de la actualizacion.
 */
void InstallGovocitos::setDescripcionActualizacion(string d)
{
	descripcionAct = d;
}