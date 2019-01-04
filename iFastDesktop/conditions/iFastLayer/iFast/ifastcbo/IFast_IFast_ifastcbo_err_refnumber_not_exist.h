#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_refnumber_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_refnumber_not_exist() { }
		~CIFast_IFast_ifastcbo_err_refnumber_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REFNUMBER_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The reference number does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The reference number does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Referenznummer existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de referencia no existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de référence inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het referentienummer bestaat niet")); }

        // Actions
	};
}



