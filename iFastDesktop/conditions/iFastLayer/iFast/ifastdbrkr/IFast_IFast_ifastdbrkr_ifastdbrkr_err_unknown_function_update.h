#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_unknown_function_update : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_unknown_function_update() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_unknown_function_update() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_UNKNOWN_FUNCTION_UPDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown function, onlly Add/Can functions allowed when updating LLPWthdrwl.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unknown function, onlly Add/Can functions allowed when updating LLPWthdrwl.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonction inconnue, seules les fonctions Ajouter/Annuler sont autorisées lors de la mise à jour du retrait REEP.")); }

        // Actions
	};
}



