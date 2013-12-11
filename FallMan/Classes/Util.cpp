#include "util.h"

USING_NS_CC;

bool Util::checkTwoRectCollisionFromTop(CCRect topRect, CCRect bottomRect){
	//topRect.intersectsRect()
	if(topRect.getMidX() <= bottomRect.getMaxX() && topRect.getMaxX() >= bottomRect.getMidX()
		&& topRect.getMidY() <= bottomRect.getMaxY() && topRect.getMaxY() >= bottomRect.getMinY()){
			return true;
	}else{
		return false;
	}
}