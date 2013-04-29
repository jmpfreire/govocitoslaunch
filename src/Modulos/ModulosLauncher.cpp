/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ModulosLauncher.cpp
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

#include "ModulosLauncher.h"

/**
 Constructor.
 */
ModulosLauncher::ModulosLauncher()
{
	instaladorVersion = 0;

	instalador = new InstallGovocitos();
}

/**
 Desctructor.
 */
ModulosLauncher::~ModulosLauncher()
{
	delete instaladorVersion, instalador;
}

/**
 Devuelve el puntero al objeto del actualizador.
 @return *DescargaActualizacion, puntero del objeto del actualizador.
 */
DescargaActualizacion *ModulosLauncher::getDescargaActualizacion()
{
	return &actualizador;
}

/**
 Devuelve el puntero al objeto de configuracion del actualizador.
 @return *ConfigLauncher, puntero del objeto de configuracion.
 */
ConfigLauncher *ModulosLauncher::getConfigLauncher()
{
	return &configuracion;
}

/**
 Devuelve el puntero al objeto del instalador.
 @return *InstallGovocitos, puntero del objeto de instalacion.
 */
InstallGovocitos *ModulosLauncher::getInstallGovocitos()
{
	return instalador;
}

/**
 Devuelve el puntero al objeto del instalador de versiones.
 @return *InstaladorVersion, puntero del objeto de instalacion de versiones.
 */
InstaladorVersion *ModulosLauncher::getInstaladorVersion()
{
	return instaladorVersion;
}

/**
 Crea un nuevo objeto de instalador de versiones con los atributos pasados po
 paremetro.
 @param ver, double con la version de la actualizacion.
 @param plat, string con la plataforma de la actualizacion.
 @param path, string con el path del xml de instalacion.
 @param desc, string con la descripcion de la actualizacion.
 */
void ModulosLauncher::crearInstaladorVersion(double ver, string plat, string path, string desc)
{
	instaladorVersion = new InstaladorVersion(ver, plat, path, desc);
}