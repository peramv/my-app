#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dicore_cannot_read_definition : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dicore_cannot_read_definition() { }
		~CBase_Ifds_dicore_dicore_cannot_read_definition() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_CANNOT_READ_DEFINITION")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is an internal problem. Current thread owns a parser. Cannot create another one")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This is an internal problem. Current thread owns a parser. Cannot create another one")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Der aktuelle Thread verfügt über einen Parser. Ein weiterer kann nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. La secuencia actual posee un analizador. No se puede crear otro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le fil actuel possède un analyseur. Impossible d'en créer un autre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit is een intern probleem. Huidige thread bezit een parser. Er kan geen andere worden gemaakt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



