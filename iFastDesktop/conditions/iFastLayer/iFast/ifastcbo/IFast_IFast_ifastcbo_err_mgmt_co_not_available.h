#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mgmt_co_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mgmt_co_not_available() { }
		~CIFast_IFast_ifastcbo_err_mgmt_co_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MGMT_CO_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Management company %mgmtco% is not available at this time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Management-Unternehmen %mgmtco% steht derzeit nicht zur Verfügung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La compañía administradora %mgmtco% no está disponible en este momento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'environnement %mgmtco% n'est pas disponible à cette heure")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Beheerbedrijf %mgmtco% is op dit moment niet beschikbaar")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact your system administrator.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an den Systemadministrator.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact your system administrator.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec votre administrateur de système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met uw systeembeheerder")); }
	};
}



