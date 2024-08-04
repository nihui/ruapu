//
//  ViewController.m
//  ruapu-ios
//
//  Created by mizu-bai on 2024/4/29.
//

#import "ViewController.h"

#define RUAPU_IMPLEMENTATION
#import "ruapu.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UILabel *labelISA;
@property (weak, nonatomic) IBOutlet UIButton *buttonRua;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.labelISA setNumberOfLines: 0];

    // init
    ruapu_init();
}

- (IBAction)ButtonRuaClick:(id)sender {
    NSMutableString *labelContents = [NSMutableString string];

    const char* const* supported = ruapu_rua();

    while (*supported) {
        [labelContents appendString: [NSString stringWithFormat: @"%s\n", *supported]];
        supported++;
    }
    
    [self.labelISA setText: labelContents];
}

@end
