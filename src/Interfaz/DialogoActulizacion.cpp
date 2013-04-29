/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoActulizacion.cpp
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

#include "DialogoActulizacion.h"
#include "InterfazLauncher.h"

/**
 Constructor.
 @param &il, referencia de InterfazLauncher el cual es el objeto principal de la
 interfaz.
 */
DialogoActulizacion::DialogoActulizacion(InterfazLauncher &il)
{
	interfaz = &il;
	
	//Iniciamos el dialogo
	InicializarGlade();

	add(*BoxActualizador);
	
	show_all();
}

/**
 Destructor.
 */
DialogoActulizacion::~DialogoActulizacion()
{

}

/**
 Actualiza el estado de la barra de progreso y su etiqueta.
 @param percent, double con el valor de progreso de la descarga.
 */
void DialogoActulizacion::actualizaEstado(double percent)
{
	string porcentaje;
	double porcentNum;

	porcentNum = percent * 100;
	porcentaje = UtilesLauncher::converString(porcentNum);
			
	if(porcentNum < 10.0)
	{
		porcentaje = porcentaje.substr(0, 4);
	}
	else
	{
		porcentaje = porcentaje.substr(0, 5);
	}

	barraProgreso->set_text(porcentaje + " %");
	
	barraProgreso->set_fraction(percent);
}

/**
 Actualiza la etiqueta que muestra la velocidad de descarga de ficheros.
 @param velocidad, double que contiene la velocidad en bytes.
 */
void DialogoActulizacion::actualizaVelocidad(double velocidad)
{
	string velocidaD;
	
	if(velocidad >= 900)
	{
		velocidaD = UtilesLauncher::converString(velocidad/1024);
		velocidaD = velocidaD.substr(0, 4);
		velocidaD = "Speed: " + velocidaD + " MB/s";
		velocidadDesc->set_text(velocidaD);
	}
	else
	{
		velocidaD = UtilesLauncher::converString(velocidad);
		velocidaD = velocidaD.substr(0, 3);
		velocidaD = "Speed: " + velocidaD + " KB/s";
		velocidadDesc->set_text(velocidaD);
	}
}

/**
 Actualiza la etiqueta con la informacion de descarga parcial y total.
 @param parcial, double que contiene la descarga parcial en bytes.
 @param total, double que contiene la descarga total en bytes.
 */
void DialogoActulizacion::actualizaInfoDescarga(double parcial, double total)
{
	string descargaT, descargaA;

	if(total > 1000)
	{
		total = total/1024;
		parcial = parcial/1024;

		descargaT = UtilesLauncher::converString(total).substr(0, 4) + " MB";
		descargaA = UtilesLauncher::converString(parcial).substr(0, 4);// + "MB";
	}
	else
	{
		descargaT = UtilesLauncher::converString(total).substr(0, 3) + " KB";
		descargaA = UtilesLauncher::converString(parcial).substr(0, 3);// + "KB";
	}

	InfoDescargaA->set_text("Downloaded " + descargaA + " from " + descargaT);

	
}

/**
 Actualiza la etiqueta con el numero de ficheros descargados y el que se esta
 descargando actualmente.
 @param fichActual, int que representa el fichero actual descargado.
 @param fichTotal, int que representa el numero total de ficheros a descargar.
 */
void DialogoActulizacion::actualizaNumFicheros(int fichActual, int fichTotal)
{
	string actual, total;

	actual = UtilesLauncher::converString(fichActual);
	total = UtilesLauncher::converString(fichTotal);
	
	NumFicherosA->set_text("Downloading " + actual + " from " + total);
}

/**
 Muestra que se ha finalizado la actualizacion del sistema correctamente.
 */
void DialogoActulizacion::FinalizaDescarga()
{
	string mensaje;

	mensaje = "System updated correctly";
	NumFicherosA->set_alignment(0.5, 0.5);
	InfoDescargaA->set_text("");
	NumFicherosA->set_text(mensaje);
	velocidadDesc->set_text("");
}

/**
 Inicializa el fichero glade que contiene la interfaz diseñada del actualizador.
 */
void DialogoActulizacion::InicializarGlade()
{
	UtilesLauncher::getWidgetGlade(UtilesLauncher::getGladeFile("DialogoActualizacion.glade"), "BoxActualizador", 
	               "BoxActualizador", &BoxActualizador,
	               "BotonCerrarA", &BotonCerrarA,
	               "InfoDescargaA", &InfoDescargaA,
	               "velocidadDesc", &velocidadDesc,
	               "NumFicherosA", &NumFicherosA,
	               "barraProgreso", &barraProgreso,
	               NULL);
	               
}

/**
 Activa el boton de cerrar el actualizador.
 */
void DialogoActulizacion::setActiveCerrar()
{
	BotonCerrarA->set_sensitive(true);
	
	BotonCerrarA->signal_clicked().connect(sigc::mem_fun(*interfaz, &InterfazLauncher::cerrarActualizador));
}