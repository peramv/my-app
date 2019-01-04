#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_no_view_data_objects_registered : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_no_view_data_objects_registered() { }
		~CIFast_IFast_dicbocore_err_no_view_data_objects_registered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_VIEW_DATA_OBJECTS_REGISTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify Account type - transactions exist for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Impossible de modifier le type de compte - des transactions existent pour ce compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoart kann nicht geändert werden – für dieses Konto existieren Transaktionen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible modificar el tipo de cuenta - Existen transacciones para esta cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier le type de compte – des transactions existent pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounttype kan niet worden gewijzigd - er zijn transacties voor dit account")); }

        // Actions
	};
}



