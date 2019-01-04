﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_dicore_date_format_not_recognized : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_dicore_date_format_not_recognized() { }
		~CIFast_Infrastructure_dicbocore_dicore_date_format_not_recognized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DATE_FORMAT_NOT_RECOGNIZED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date format not recognized. Check the enumeration in ddate.hpp for recognized formats.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date format not recognized. Check the enumeration in ddate.hpp for recognized formats.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datumsformat wurde nicht erkannt. Überprüfen Sie die Aufzählung in ddate.hpp nach erkannten Formaten.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Formato de fecha no reconocido. Verifique la enumeración en ddate.hpp para ver los formatos reconocidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de date non reconnu. Vérifiez l'énumération dans le fichier ddate.hpp pour voir les formats reconnus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Datumnotatie wordt niet herkend. Controleer de opsomming in ddate.hpp voor toegestane notaties")); }

        // Actions
	};
}



