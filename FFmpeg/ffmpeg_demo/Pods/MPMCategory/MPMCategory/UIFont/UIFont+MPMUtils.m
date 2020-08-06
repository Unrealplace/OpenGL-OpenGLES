//
//  UIFont+MPMUtils.m
//  abc
//
//  Created by Done.L on 2019/6/26.
//  Copyright © 2019 Done.L. All rights reserved.
//

#import "UIFont+MPMUtils.h"

@implementation UIFont (MPMUtils)

// 思源黑体 - Regular
+ (UIFont *)meipingmi_SourceHanSansCN_Regular:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"SourceHanSansCN-Regular" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// 思源黑体 - Normal
+ (UIFont *)meipingmi_SourceHanSansCN_Normal:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"SourceHanSansCN-Normal" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// 思源黑体 - Medium
+ (UIFont *)meipingmi_SourceHanSansCN_Medium:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"SourceHanSansCN-Medium" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// 思源黑体 - Bold
+ (UIFont *)meipingmi_SourceHanSansCN_Bold:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"SourceHanSansCN-Bold" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// 苹方 - Regular
+ (UIFont *)meipingmi_PingFangSC_Regular:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Regular" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// 苹方 - Medium
+ (UIFont *)meipingmi_PingFangSC_Medium:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Medium" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// 苹方 - Semibold
+ (UIFont *)meipingmi_PingFangSC_Semibold:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Semibold" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// 苹方 - Light
+ (UIFont *)meipingmi_PingFangSC_Light:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"PingFangSC-Light" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// DINAlternate-Bold
+ (UIFont *)meipingmi_DINAlternate_Bold:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"DIN-Bold" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// DINPro-Regular
+ (UIFont *)meipingmi_DINPro_Regular:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"DIN-Regular" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// DINPro-Medium
+ (UIFont *)meipingmi_DINPro_Medium:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"DIN-Medium" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// DIN-Bold
+ (UIFont *)meipingmi_DIN_Bold:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"DIN-Bold" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

// Helvetica
+ (UIFont *)meipingmi_Helvetica:(CGFloat)fontSize {
    UIFont *font = [UIFont fontWithName:@"Helvetica" size:fontSize];
    if (!font) {
        font = [UIFont systemFontOfSize:fontSize];
    }
    
    return font;
}

@end
