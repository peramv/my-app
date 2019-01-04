#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_contact_person_lastname_cannot_be_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_contact_person_lastname_cannot_be_blank() { }
		~CIFast_IFast_ifastcbo_err_contact_person_lastname_cannot_be_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTACT_PERSON_LASTNAME_CANNOT_BE_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The last name of the contact person can not be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The last name of the contact person can not be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nom de famille de la personne-ressource est requis.")); }

        // Actions
	};
}



