/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * InterfazLauncher.cpp
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

#include "InterfazLauncher.h"
#include "NucleoLauncher.h"

/**
 Constructor, establece el tamaño de la ventana, nombre y icono.
 */
InterfazLauncher::InterfazLauncher()
{
	set_title("Govocitos Updater");
	set_default_size(500, 80);
	set_icon_from_file(UtilesLauncher::getIconoFile("logoGovocitos.png"));

	dialogoSelecAct = new DialogoSeleccionAct();
	
	add(*dialogoSelecAct);
}

/**
 Destructor.
 */
InterfazLauncher::~InterfazLauncher()
{
	delete dialogoActualiza, dialogoSelecAct;
}

/**
 Establece la referencia al controlador de la aplicacion.
 @param &nl, referencia a NucleoLauncher que es el objeto que controla la comunicacion
 entre el modelo y la vista.
 */
void InterfazLauncher::setControlador(NucleoLauncher &nl)
{
	controladorLaunch = &nl;
}

/**
 Comprueba si hay actualizaciones nuevas del programa.
 */
void InterfazLauncher::comprobarActualizaciones()
{	
	controladorLaunch->iniciarActualizacion();
}

/**
 Activa el boton de cerrar el actualizacion.
 */
void InterfazLauncher::cerrarPanelActualizaciones()
{
	dialogoActualiza->setActiveCerrar();
}

/**
 Crea el dialogo de actualizacion y elimina el dialogo de notas.
 */
void InterfazLauncher::crearDialogoActuliazcion()
{
	this->remove();

	this->resize(400, 150);

	UtilesLauncher::actualizarInterfaz();
	
	//Creamos el dialogo de Actualizacion
	dialogoActualiza = new DialogoActulizacion(*this);

	add(*dialogoActualiza);

	UtilesLauncher::actualizarInterfaz();
}

/**
 Cierra el actualizador.
 */
void InterfazLauncher::cerrarActualizador()
{
	UtilesLauncher::actualizarInterfaz();	
	hide();
}

/**
 Devuelve un puntero del dialogo de actualizacion.
 @return *DialogoActualizacion, puntero del objeto del dialogo de actualizacion.
 */
DialogoActulizacion *InterfazLauncher::getDialogoActualizacion()
{
	return dialogoActualiza;
}

/**
 Devuelve un puntero del dialogo de notas de actualizacion.
 @return *DialogoSeleccionAct, puntero del objeto del dialogo de notas de version.
 */
DialogoSeleccionAct *InterfazLauncher::getDialogoSeleccionAct()
{
	return dialogoSelecAct;
}