#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_no_mail_to_suppress : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_no_mail_to_suppress() { }
		~CIFast_IFast_ifastcbo_warn_no_mail_to_suppress() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NO_MAIL_TO_SUPPRESS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no Mail, Fax, CD, Email or Epost to suppress for document type:%DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun courrier, télécopie, CD, courriel ou postel à supprimer pour le type de document :%DOCTYPE%.")); }

        // Actions
	};
}



