#import <Cocoa/Cocoa.h>
#import "file.h"

void showSavePanel() {
    NSSavePanel *panel = [NSSavePanel savePanel];
    [panel runModal];
    // You can handle the selected file URL or further actions here
}

- (IBAction)saveButtonClicked:(id)sender {
    NSSavePanel *panel = [NSSavePanel savePanel];
    [panel runModal];
    // Once the user saves the file, you can handle the selected file URL or further actions here
    NSURL *selectedURL = [panel URL];
    // Further actions with the selectedURL
}
