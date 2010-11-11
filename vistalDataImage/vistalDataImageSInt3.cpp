// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "Image3D.hh"
#include "vistalDataImageSInt3.h"
#include "itkImage3D.hh"

#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// vistalDataImageSInt3Private
// /////////////////////////////////////////////////////////////////

class vistalDataImageSInt3Private
{
public:
  vistal::Image3D<int> * image;
	itkImage3D<int> * itkConverter;
};

// /////////////////////////////////////////////////////////////////
// vistalDataImageSInt3
// /////////////////////////////////////////////////////////////////

vistalDataImageSInt3::vistalDataImageSInt3(void) : dtkAbstractDataImage(), d(new vistalDataImageSInt3Private)
{
  d->image = 0;
	d->itkConverter = 0;
}

vistalDataImageSInt3::~vistalDataImageSInt3(void)
{

}

bool vistalDataImageSInt3::registered(void)
{
    return dtkAbstractDataFactory::instance()->registerDataType("vistalDataImageSInt3", createVistalDataImageSInt3);
}

QString vistalDataImageSInt3::description(void) const
{
    return "vistalDataImageSInt3";
}

void *vistalDataImageSInt3::data()
{
  return d->image;
}

void *vistalDataImageSInt3::output()
{
	if (!d->itkConverter)
		d->itkConverter = new itkImage3D<int>;

	if (!d->image)
		return 0;

	d->itkConverter->SetImage3D(*d->image);

	return d->itkConverter->GetOutput();
}

void vistalDataImageSInt3::setData(void* data)
{
  d->image = static_cast<vistal::Image3D<int> *> (data);
}

int vistalDataImageSInt3::xDimension(void)
{
  if (d->image != NULL)
    return d->image->nbx;
  else
    return -1;
}

int vistalDataImageSInt3::yDimension(void)
{
  if (d->image != NULL)
    return d->image->nby;
  else
    return -1;
}

int vistalDataImageSInt3::zDimension(void)
{
  if (d->image != NULL)
    return d->image->nbz;
  else
    return -1;
}

int vistalDataImageSInt3::tDimension(void)
{
  if (d->image != NULL)
    return d->image->nbt;
  else
    return -1;
}


// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractData *createVistalDataImageSInt3(void)
{
    return new vistalDataImageSInt3;
}