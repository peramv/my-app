#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_disessn_disessn_awd_work_created : public CConditionObject
	{
	public:
		CBase_Infrastructure_disessn_disessn_awd_work_created() { }
		~CBase_Infrastructure_disessn_disessn_awd_work_created() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DISESSN_AWD_WORK_CREATED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("disessn")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD work was successfully created.  %WorkObjectDetails%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD work was successfully created.  %WorkObjectDetails%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Erstellung der AWD-Arbeit war erfolgreich.  %WorkObjectDetails%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tarea de AWD se creó con éxito.  %WorkObjectDetails%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le travail AWD a été créé avec succès. %WorkObjectDetails%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-werk is gemaakt.  %WorkObjectDetails%")); }

        // Actions
	};
}



