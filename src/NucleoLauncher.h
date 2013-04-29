/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * NucleoLauncher.h
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

#ifndef _NUCLEOLAUNCHER_H_
	#define _NUCLEOLAUNCHER_H_

	#include <gtkmm/main.h>
	#include <iostream>
	#include <string>

	#include "Modulos/ModulosLauncher.h"
	#include "Interfaz/InterfazLauncher.h"
	#include "Modulos/XmlWebVersion.h"
	#include "Modulos/XmlInstalador.h"
	#include "Modulos/ConexionBD.h"
	#include "UtilesLauncher.h"

	class NucleoLauncher
	{
		public:
			NucleoLauncher();
			~NucleoLauncher();
			InterfazLauncher *getInterfazLaunch();
			bool comprobarNuevasActualizaciones();
			void iniciarActualizacion();
			bool obtenerDatosDeActualizacion();
			bool descargaDatos();
			void skipVersionActual();
			void remindLaterVersion();
		private:
			//Metodos
			bool borraCacheDescarga(InstaladorVersion &iv, int i);
			//Atributos
			InterfazLauncher *interfazLaunch;
			ModulosLauncher *modeloLaunch;
	};

#endif //_NUCLEOLAUNCHER_H_