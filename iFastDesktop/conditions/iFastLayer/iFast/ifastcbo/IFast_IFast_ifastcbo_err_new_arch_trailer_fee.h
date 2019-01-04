#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_new_arch_trailer_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_new_arch_trailer_fee() { }
		~CIFast_IFast_ifastcbo_err_new_arch_trailer_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEW_ARCH_TRAILER_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This environment supports new Trailer Fee architecture. Please use new Trailer Fee Setup screen.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cet environnement supporte la nouvelle architecture des frais administratifs. Veuillez utiliser le nouvel écran de réglage des frais administratifs.")); }

        // Actions
	};
}



