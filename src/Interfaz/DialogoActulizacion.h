/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoActulizacion.h
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

#ifndef _DIALOGOACTUALIZACION_H_
	#define _DIALOGOACTUALIZACION_H_

	#include <gtkmm.h>

	#include "UtilesLauncher.h"

	class InterfazLauncher;

	class DialogoActulizacion : public Gtk::HBox
	{
		public:
			DialogoActulizacion(InterfazLauncher &il);
			~DialogoActulizacion();
			void actualizaEstado(double percent);
			void actualizaVelocidad(double velocidad);
			void actualizaInfoDescarga(double parcial, double total);
			void actualizaNumFicheros(int fichActual, int fichTotal);
			void FinalizaDescarga();
			void setActiveCerrar();
		private:
			//Metodos
			void InicializarGlade();
			//Atributos
			Gtk::VBox *BoxActualizador;
			Gtk::Button *BotonCerrarA;
			Gtk::Label *InfoDescargaA, *velocidadDesc, *NumFicherosA;
			Gtk::ProgressBar *barraProgreso;
			InterfazLauncher *interfaz;
	};
#endif //_DIALOGOACTUALIZACION_H_