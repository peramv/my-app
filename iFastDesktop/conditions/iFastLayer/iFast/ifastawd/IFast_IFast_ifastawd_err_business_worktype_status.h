#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastawd_err_business_worktype_status : public CConditionObject
	{
	public:
		CIFast_IFast_ifastawd_err_business_worktype_status() { }
		~CIFast_IFast_ifastawd_err_business_worktype_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BUSINESS_WORKTYPE_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastawd")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Business area, work type and status can not be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Business area, work type and status can not be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le secteur de marché, le type de travail et le statut sont requis.")); }

        // Actions
	};
}



