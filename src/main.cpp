/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cpp
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

#include <stdio.h>
#include <stdlib.h>
#include <gtkmm/main.h>

#ifdef G_OS_WIN32
#include <process.h>
#endif

#include "NucleoLauncher.h"

using namespace std;

/**
 Metodo main del actualizador, se ejecuta el acutalizador y una vez finalizado
 se crea un nuevo hilo para lanzar el govocitos y acto seguido finaliza la
 ejecucion del actualizador
 */
int main (int argc, char *argv[])
{	
	Gtk::Main kit(argc, argv);

	//Cremos el controlador
	NucleoLauncher *controlador = new NucleoLauncher();

	//Comprobamos si hay nuevas actualizaciones
	if(controlador->comprobarNuevasActualizaciones())
	{
		//Lanzamos la interfaz grafica
		Gtk::Main::run(*controlador->getInterfazLaunch());
	}

	//Ejecutamos govocitos windows
	#ifdef G_OS_WIN32
		spawnv(P_OVERLAY, Glib::find_program_in_path("govocitos.exe").c_str(), argv);
	#else
	//Ejecutamos en linux
		pid_t pid=fork();
	
		if (pid==0) 
		{
			execv(Glib::find_program_in_path("govocitos").c_str(), NULL);
		}
	#endif

	return 0;
}
