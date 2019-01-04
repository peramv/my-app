#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sin_different_for_trf_protectedfund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sin_different_for_trf_protectedfund() { }
		~CIFast_IFast_ifastcbo_err_sin_different_for_trf_protectedfund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SIN_DIFFERENT_FOR_TRF_PROTECTEDFUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SIN number is different between the transfer from and transfer to account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SIN number is different between the transfer from and transfer to account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("SIN number is different between the transfer from and transfer to account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS est différent pour les comptes d'origine du transfert et de cible du transfert.")); }

        // Actions
	};
}



