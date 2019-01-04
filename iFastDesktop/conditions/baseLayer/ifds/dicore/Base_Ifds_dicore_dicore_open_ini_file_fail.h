#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dicore_open_ini_file_fail : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dicore_open_ini_file_fail() { }
		~CBase_Ifds_dicore_dicore_open_ini_file_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_OPEN_INI_FILE_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This an internal problem. Current thread doesn't own the parser. Cannot delete parser")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This an internal problem. Current thread doesn't own the parser. Cannot delete parser")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Der aktuelle Thread hat keinen Parser. Parser kann nicht gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. La secuencia actual no posee un analizador. No se puede eliminar el analizador.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le fil actuel ne possède pas d'analyseur. Impossible de supprimer l'analyseur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit is een intern probleem. Huidige thread is niet de eigenaar van de parser. Parser kan niet worden gewist")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



