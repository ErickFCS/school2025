import { z } from "zod";


export const deviceSchema = z.object({
    password: z.string().min(1, "Password is required"),
    startTime: z.string().datetime().default((new Date()).toISOString())
});

export type Device = z.infer<typeof deviceSchema>

export const deviceWithIdSchema = deviceSchema.extend({
    id: z.number().positive("The ids must be positive")
});

export type DeviceWithId = z.infer<typeof deviceWithIdSchema>
