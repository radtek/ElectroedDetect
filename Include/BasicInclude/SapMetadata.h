#ifndef _SAPMETADATA_H_
#define _SAPMETADATA_H_

#include "SapClassBasicDef.h"

//
// Interface that any compliant device must implement
//
class SAPCLASSBASIC_CLASS ISapMetadata
{
public:

   virtual ~ISapMetadata(){};

   virtual BOOL Enable(BOOL enable) = 0;
   virtual BOOL IsEnabled() const = 0;

   virtual UINT GetSelectorCount() const = 0;
   virtual BOOL GetSelectorName(UINT selectorIndex, char* name, UINT nameLength) const = 0;

   virtual BOOL Select(UINT selectorIndex, BOOL select) = 0;
   virtual BOOL IsSelected(UINT selectorIndex) = 0;

   virtual BOOL Extract(UINT bufferIndex) = 0;
   virtual BOOL Extract(UINT bufferIndex, UINT lineIndex) = 0;

   virtual UINT GetExtractedResultCount() const = 0;
   virtual BOOL GetExtractedResult(UINT resultIndex, char* name, UINT nameLength, char* value, UINT valueLength) const = 0;

   virtual BOOL SaveToCSV(const char* filename) = 0;
};

//
// SapMetadata class declaration
//

class SAPCLASSBASIC_CLASS SapMetadata : public SapManager, ISapMetadata
{
public:

   // Metadata types
   typedef int MetadataType;
   enum _MetadataType
   {
      MetadataUnknown,
      MetadataPerFrame,
      MetadataPerLine
   };

public:

   // Constructor/Destructor
   SapMetadata(SapAcqDevice* pAcqDevice, SapBuffer* pBuffer, BOOL alwaysAllocExtraLines = TRUE);
   virtual ~SapMetadata();

   // Helper function to verify the acquisiton device supports metadata
   static BOOL IsMetadataSupported(SapAcqDevice* pAcqDevice);

   // Helper function to verify the acquisiton device metadata support is enabled
   static BOOL IsMetadataEnabled(SapAcqDevice* pAcqDevice);

   // Helper function to check the metadata type the acquisiton device supports
   static MetadataType GetMetadataType(SapAcqDevice* pAcqDevice);

   // Module create/destroy
   BOOL Create();
   BOOL Destroy();

   // Get the metadata type of this created module
   MetadataType GetMetadataType() const;

   // Enable/Disable metadata for this acquisition device
   BOOL Enable(BOOL enable = TRUE);
   BOOL IsEnabled() const;

   // Get the list of metadata selectors this acquisition device provides
   UINT GetSelectorCount() const;
   BOOL GetSelectorName(UINT selectorIndex, char* name, UINT nameLength) const;

   // Enable/Disable a specific selector
   BOOL Select(UINT selectorIndex, BOOL select = TRUE);
   BOOL IsSelected(UINT selectorIndex);

   // Extract the metadata items from the buffer
   BOOL Extract();
   BOOL Extract(UINT bufferIndex);
   BOOL Extract(UINT bufferIndex, UINT lineIndex);

   // Get the list of extracted metadata items
   UINT GetExtractedResultCount() const;
   BOOL GetExtractedResult(UINT resultIndex, char* name, UINT nameLength, char* value, UINT valueLength) const;

   // Export the previously extracted metadata items to a comma separated values file
   // for later exploitation with a spreadsheet software
   BOOL SaveToCSV(const char* filename);

protected:
   // Utility methods
   static BOOL IsDeviceVendorSupported(SapAcqDevice* pAcqDevice);

private:
   SapAcqDevice* m_pAcqDevice;
   SapBuffer* m_pBuffer;
   ISapMetadata* m_pAgent;
   MetadataType  m_type;
   BOOL m_alwaysAllocExtraLines;
};

#endif