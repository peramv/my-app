﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_dilution_link_id_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_dilution_link_id_does_not_exist() { }
		~CIFast_IFast_ifastdbrkr_err_dilution_link_id_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DBRKR_DILUTION_LINK_ID_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Dilution Link ID does not exist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’identification du lien de dilution n’existe pas.")); }

        // Actions
	};
}