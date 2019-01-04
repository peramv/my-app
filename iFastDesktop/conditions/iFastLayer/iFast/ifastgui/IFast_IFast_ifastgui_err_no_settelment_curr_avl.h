#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_err_no_settelment_curr_avl : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_err_no_settelment_curr_avl() { }
		~CIFast_IFast_ifastgui_err_no_settelment_curr_avl() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_SETTELMENT_CURR_AVL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Currency and Tax type rule currency does not have common set of currencies")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La devise du fonds et celle de la règle du type d'impôt ne correspondent pas.")); }

        // Actions
	};
}



