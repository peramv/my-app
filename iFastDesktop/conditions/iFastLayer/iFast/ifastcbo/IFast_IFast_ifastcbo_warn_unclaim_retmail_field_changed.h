#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_unclaim_retmail_field_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_unclaim_retmail_field_changed() { }
		~CIFast_IFast_ifastcbo_warn_unclaim_retmail_field_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_UNCLAIM_RETMAIL_FIELD_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is change in unclaimed property due to return mail related, do you accept this change.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un changement aux biens non réclamés en raison d'un retour de courrier connexe. Acceptez-vous ce changement?")); }

        // Actions
	};
}



