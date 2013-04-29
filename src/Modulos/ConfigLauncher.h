/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConfigLauncher.h
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

#ifndef _CONFIGLAUNCHER_H_
	#define _CONFIGLAUNCHER_H_

	#include <iostream>
	#include <fstream>
	#include <string.h>

	#include "UtilesLauncher.h"

	const unsigned int MAXRUTA = 150;

	using namespace std;

	class ConfigLauncher
	{   
		public:
			ConfigLauncher();
			~ConfigLauncher();
			int getVersion();
			void setVersion(int v);
			string getPathXmlVeriones();
			void escribFichConfig(string ruta, ConfigLauncher &data);
		private:
			//Metodos
			bool leerFichConfig(string ruta, ConfigLauncher &data);
			void creaDirectorio(string path);
			//Atributos
			int version;
			char pathVersion[MAXRUTA];
	};
#endif //_CONFIGLAUNCHER_H_