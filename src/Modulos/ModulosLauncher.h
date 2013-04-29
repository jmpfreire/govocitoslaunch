/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ModulosLauncher.h
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

#ifndef _MODULOSLAUNCHER_H_
	#define _MODULOSLAUNCHER_H_

	#include "DescargaActualizacion.h"
	#include "ConfigLauncher.h"
	#include "InstallGovocitos.h"
	#include "InstaladorVersion.h"

	class ModulosLauncher
	{
		public:
			ModulosLauncher();
			~ModulosLauncher();
			DescargaActualizacion *getDescargaActualizacion();
			ConfigLauncher *getConfigLauncher();
			InstallGovocitos *getInstallGovocitos();
			InstaladorVersion *getInstaladorVersion();
			void crearInstaladorVersion(double ver, string plat, string path, string desc);
		private:
			DescargaActualizacion actualizador;
			ConfigLauncher configuracion;
			InstallGovocitos *instalador;
			InstaladorVersion *instaladorVersion;
	};

#endif //_MODULOSLAUNCHER_H_