#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_diawdi_diawdi_load_proc_fail : public CConditionObject
	{
	public:
		CBase_Ifds_diawdi_diawdi_load_proc_fail() { }
		~CBase_Ifds_diawdi_diawdi_load_proc_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWDI_LOAD_PROC_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("diawdi")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Host connection manager not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Host connection manager not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Eingabe. Einige der Zeichen sind eventuell keine Ziffern.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el administrador de la conexión con el host.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'exploitant de connexion de l'hôte est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verbindingsmanager host is niet gevonden.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("NULL")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("NULL")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie den Wert erneut ein")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("NUL")); }
	};
}



