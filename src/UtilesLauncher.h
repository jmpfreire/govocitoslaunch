/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * UtilesLauncher.h
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

#ifndef _UTILESLAUNCHER_H_
	#define _UTILESLAUNCHER_H_

	#include <libglademm/xml.h>
	#include <gtkmm.h>
	#include <iostream>
	#include <string>

	using namespace std;

	class UtilesLauncher
	{
		public:
			static void getWidgetGlade(string filename,const char* root_node,const char *widget_name,...);
			static string getDataDir();
			static string getGladeFile(string file);
			static string getIconoFile(string file);
			static string converString(double valor);
			static string converString(int valor);
			static void actualizarInterfaz();
			static string obtenerDireccionConfig();
			static string direccionConfig(string fichero);
			static string obtenerDireccionCache();
			static string direccionCache(string fichero);
			static bool borraFicheroSistema(string ruta);
			static int convertStringToInt(string cadena);
			static void dialogoError(string t, string title);
	};
#endif //_UTILESLAUNCHER_H_