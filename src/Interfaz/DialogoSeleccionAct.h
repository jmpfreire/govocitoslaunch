/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * DialogoSeleccionAct.h
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

#ifndef _DIALOGOSELECCIONACT_H_
	#define _DIALOGOSELECCIONACT_H_

	#include <gtkmm.h>

	#include "UtilesLauncher.h"

	class DialogoSeleccionAct : public Gtk::HBox
	{
		public:
			DialogoSeleccionAct();
			~DialogoSeleccionAct();
			Gtk::Button *getUpdateButton();
			Gtk::Button *getRemindLaterButton();
			Gtk::Button *getSkipVersionButton();
			Gtk::TextView *getTextViewDescripcion();
		private:
			//Metodos
			void InicializarGlade();
			//Atributos
			Gtk::VBox *vboxRelease;			
			Gtk::Image *ImageLogoG;
			Gtk::Button *updateBotonG, *remindLaterG, *skipVersionG;
			Gtk::TextView *notesVersionG;
	};
#endif //_DIALOGOSELECCIONACT_H_