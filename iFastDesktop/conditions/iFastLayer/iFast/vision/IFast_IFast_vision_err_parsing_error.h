#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_vision_err_parsing_error : public CConditionObject
	{
	public:
		CIFast_IFast_vision_err_parsing_error() { }
		~CIFast_IFast_vision_err_parsing_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PARSING_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Parsing error. Code: %code%. Message: %message%. Line: %line%. Column: %column%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Parsing error. Code: %code%. Message: %message%. Line: %line%. Column: %column%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Parsing-Fehler. Code: %code% Meldung: %message%. Zeile: %line%. Spalte: %column%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de análisis. Código: %code%. Mensaje: %message%. Línea: %line%. Columna: %column%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'analyse syntaxique. Code : %code%. Message : %message%. Ligne : %line%. Colonne : %column%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Parsing-fout.  Code: %code%. Bericht: %message%. Regel: %line%. Kolom: %column%")); }

        // Actions
	};
}



