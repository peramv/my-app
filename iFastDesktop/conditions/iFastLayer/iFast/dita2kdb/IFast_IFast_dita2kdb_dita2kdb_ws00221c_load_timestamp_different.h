#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_load_timestamp_different : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_load_timestamp_different() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_load_timestamp_different() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_LOAD_TIMESTAMP_DIFFERENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GUI function security is not yet set up, please contact technical support.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La securite de la fonction interface graphique n'est pas encore installee, veuillez contacter l'assistance technique.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzeroberflächen-Funktions-Sicherheit ist noch nicht erstellt, wenden Sie sich bitte an den technischen Support.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Aún no se ha configurado la seguridad de la función GUI, por favor póngase en contacto con el soporte técnico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La protection de la fonction GUI n'est pas encore réglée. Veuillez communiquer avec le soutien technique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("GUI-functiebeveiliging is nog niet ingesteld, neem contact op met de technische dienst")); }

        // Actions
	};
}



