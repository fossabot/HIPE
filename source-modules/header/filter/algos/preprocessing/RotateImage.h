//READ LICENSE BEFORE ANY USAGE
/* Copyright (C) 2018  Damien DUBUC ddubuc@aneo.fr (ANEO S.A.S)
 *  Team Contact : hipe@aneo.fr
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *  
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  
 *  In addition, we kindly ask you to acknowledge ANEO and its authors in any program 
 *  or publication in which you use HIPE. You are not required to do so; it is up to your 
 *  common sense to decide whether you want to comply with this request or not.
 *  
 *  Non-free versions of HIPE are available under terms different from those of the General 
 *  Public License. e.g. they do not require you to accompany any object code using HIPE 
 *  with the corresponding source code. Following the new licensing any change request from 
 *  contributors to ANEO must accept terms of re-license by a general announcement. 
 *  For these alternative terms you must request a license from ANEO S.A.S Company 
 *  Licensing Office. Users and or developers interested in such a license should 
 *  contact us (hipe@aneo.fr) for more information.
 */

#pragma once
#include <corefilter/tools/RegisterTools.hpp>
#include <corefilter/IFilter.h>
#include <core/HipeStatus.h>
#include <coredata/ConnexData.h>
#include <data/ImageData.h>

#pragma warning(push, 0)
#include <opencv2/highgui/highgui.hpp>
#pragma warning(pop)

namespace filter
{
	namespace algos
	{
		/**
		 * \var RotateImage::angle
		 * The angle (in degrees) to rotate the image by.
		 */

		/**
		 * \brief The RotateImage filter is used to rotate images around the positive Z axis and taking their center as pivot.
		 */
		class RotateImage : public IFilter
		{
			//data::ConnexData<data::ImageArrayData, data::ImageArrayData> _connexData;
			CONNECTOR(data::ImageArrayData, data::ImageArrayData);

			REGISTER(RotateImage, ()), _connexData(data::INOUT)
			{

				angle = 10;
			}

			REGISTER_P(double, angle);

			~RotateImage()
			{

			}

			virtual std::string resultAsString()
			{
				return std::string("TODO");
			};

		public:
			HipeStatus process()
			{
				while (!_connexData.empty()) // While i've parent data
				{
					data::ImageArrayData images = _connexData.pop();


					//Resize all images coming from the same parent
					for (auto &myImage : images.Array())
					{
						cv::Point2f src_center(myImage.cols / 2.0F, myImage.rows / 2.0F);
						cv::Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);

						warpAffine(myImage, myImage, rot_mat, myImage.size());
					}
					//No push it's an inout data
				}

				return OK;
			}

			void dispose()
			{
				Model::dispose();
				cv::destroyWindow(_name);
			}
		};

		ADD_CLASS(RotateImage, angle);
	}
}
