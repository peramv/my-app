#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_nominee_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_nominee_required() { }
		~CIFast_IFast_ifastcbo_err_nominee_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOMINEE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A Nominee owner is required to be set up for this type of account designations.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("A Nominee owner is required to be set up for this type of account designations.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für diese Art der Kontozuweisung muss ein bevollmächtigter Eigentümer erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse un propietario nominatario para este tipo de designaciones de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un propriétaire nominé doit être réglé pour ce type de désignations de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gemachtigde eigenaar moet worden ingesteld voor dit type account")); }

        // Actions
	};
}



