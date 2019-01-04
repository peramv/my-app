#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_index_out_of_range : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_index_out_of_range() { }
		~CBase_Ifds_didbrkr_didbrkr_index_out_of_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_INDEX_OUT_OF_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This method should never be called directly.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This method should never be called directly.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Diese Methode sollte nie direkt aufgerufen werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este método no debe llamarse nunca directamente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette méthode ne devrait jamais être appelée directement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deze methode mag nooit direct worden aangeroepen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den CBO-Code.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código CBO.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code d'optimisation de coûts.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de CBO-code")); }
	};
}



