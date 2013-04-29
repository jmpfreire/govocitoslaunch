/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DescargaActualizacion.h
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

#ifndef _DESCARGAACTUALIZACION_H_
	#define _DESCARGAACTUALIZACION_H_

	#include <gtkmm.h>
	#include <iostream>
	#include <stdio.h>
	#include <curl/curl.h> 

	#include "UtilesLauncher.h"
	#include "Interfaz/DialogoActulizacion.h"

	/*-------------Importante-------------------
	Para la compilacion en windows de libcurl hay que añadir lo siguiente
	fichero fileinfo.h de la libreria gtk #undef FILE_TYPE_UNKNOWN 
	fichero error.h de la libreria gtk #undef HOST_NOT_FOUND
	-------------------------------------------*/

	using namespace std;

	class DescargaActualizacion
	{
		public:
			DescargaActualizacion();
			~DescargaActualizacion();
			void setDialogoProgreso(DialogoActulizacion &da);
			bool descargaDatos(string path, string ruta);
			bool descargaFicheroXml(string path, string nombreFich);
			friend int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
	};

#endif //_DESCARGAACTUALIZACION_H_