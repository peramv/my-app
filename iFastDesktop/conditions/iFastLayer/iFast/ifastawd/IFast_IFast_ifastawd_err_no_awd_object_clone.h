#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastawd_err_no_awd_object_clone : public CConditionObject
	{
	public:
		CIFast_IFast_ifastawd_err_no_awd_object_clone() { }
		~CIFast_IFast_ifastawd_err_no_awd_object_clone() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_AWD_OBJECT_CLONE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastawd")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no AWD object to clone.  Make sure there is an AWD object in the container.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("There is no AWD object to clone.  Make sure there is an AWD object in the container.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucun objet AWD à cloner. Assurez-vous qu'il y a un objet AWD dans le conteneur.")); }

        // Actions
	};
}



